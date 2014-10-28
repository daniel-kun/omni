#include "sandbox_selector_model.hpp"
#include "sandbox_widget.hpp"
#include <omni/ui/literal_expression_view.hpp>
#include <omni/ui/entity_toggle_widget.hpp>
#include <omni/ui/entity_widget_provider.hpp>
#include <omni/ui/variable_declaration_expression_view.hpp>
#include <omni/ui/entity_placeholder_widget.hpp>

#include <omni/core/invalid_argument_error.hpp>
#include <omni/core/context.hpp>
#include <omni/core/model/type.hpp>
#include <omni/core/model/builtin_literal_expression.hpp>
#include <omni/core/model/module.hpp>
#include <omni/core/model/function.hpp>
#include <omni/core/model/block.hpp>
#include <omni/core/model/return_statement.hpp>

#include <QLibrary>
#include <QMessageBox>

#include <boost/filesystem.hpp>

#include <sstream>
#include <functional>

using creator_function = std::function <std::unique_ptr <omni::forge::sandbox_widget> (omni::core::context & context, QWidget & parent)>;

class omni::forge::sandbox_selector_model::sandbox_selector_data_base {
public:
    sandbox_selector_data_base (
        sandbox_selector_data_base * parent,
        QString title,
        QString description,
        creator_function creator,
        std::vector <std::shared_ptr <sandbox_selector_data_base>> children = std::vector <std::shared_ptr <sandbox_selector_data_base>> ());

    sandbox_selector_data_base * parent;
    QString title;
    QString description;
    std::unique_ptr <sandbox_widget> widget;
    creator_function creator;

    std::vector <std::shared_ptr <sandbox_selector_data_base>> children;
};

omni::forge::sandbox_selector_model::sandbox_selector_data_base::sandbox_selector_data_base (
    sandbox_selector_data_base * parent,
    QString title,
    QString description,
    creator_function creator,
    std::vector <std::shared_ptr <sandbox_selector_data_base>> children) :
    parent (parent),
    title (title),
    description (description),
    widget (),
    creator (creator),
    children (children)
{
}

namespace {
template <typename Widget>
std::unique_ptr <Widget> createWidget (QWidget &parent)
{
    return std::make_unique <Widget> (&parent);
}

template <typename Widget>
class sandbox_selector_data : public omni::forge::sandbox_selector_model::sandbox_selector_data_base {
public:
    sandbox_selector_data (
        QString title,
        QString description,
        creator_function creator,
        std::vector <std::shared_ptr <sandbox_selector_data_base>> children = std::vector <std::shared_ptr <sandbox_selector_data_base>> ()) :
        sandbox_selector_data_base (
            nullptr,
            title,
            description, 
            creator,
            children)
    {
    }
};

template <>
class sandbox_selector_data <void>: public omni::forge::sandbox_selector_model::sandbox_selector_data_base {
public:
    sandbox_selector_data (
        QString title,
        QString description,
        std::vector <std::shared_ptr <sandbox_selector_data_base>> children = std::vector <std::shared_ptr <sandbox_selector_data_base>> ()) :
        sandbox_selector_data_base (
            nullptr,
            title,
            description, 
            [] (omni::core::context &, QWidget &) -> std::unique_ptr <omni::forge::sandbox_widget> {
                return std::unique_ptr <omni::forge::sandbox_widget> ();
            },
            children)
    {
    }
};

void setParents (omni::forge::sandbox_selector_model::sandbox_selector_data_base & item)
{
    for (auto & i : item.children) {
        i->parent = & item;
        setParents (*i);
    }
}

/*
Creates an entity_toggle_widget with an entity_widget_provider named "literal_expression" in a sandbox_widget container to be shown in the main_window.
*/
std::unique_ptr <omni::forge::sandbox_widget> createLiteralView (omni::core::context & context, QWidget & parent)
{
    auto literal = std::make_shared <omni::core::model::builtin_literal_expression <int>> (context, 42);
    QWidget & localParent (parent);
    // For editor and layout, we rely on Qt's object ownership mechanism to free them:
    auto * editor = new omni::ui::entity_toggle_widget (context, omni::ui::entity_widget_provider::getProvider ("literal_expression"), & parent);
    auto result = std::make_unique <omni::forge::sandbox_widget> (
        parent,
        [editor, & localParent] (omni::core::context &, omni::core::model::module & module) -> void {
            auto literalExpression = std::dynamic_pointer_cast <omni::core::model::literal_expression> (editor->getEntity ());
            auto body = std::make_shared <omni::core::model::block> ();
            body->appendStatement (std::make_shared <omni::core::model::return_statement> (literalExpression));
            auto fun = module.createFunction (
                "test",
                literalExpression->getType (),
                body);
            fun->setExported (true);
            std::string libraryFileName = 
                (boost::filesystem::temp_directory_path() /
                boost::filesystem::unique_path ("omni-sandbox-%%%%%%%%%%%.dll")).string ();
            module.emitSharedLibraryFile (libraryFileName);
            module.removeFunction (fun);
            QLibrary lib (QString::fromStdString (libraryFileName));
            auto realFunc = reinterpret_cast <int (*) ()> (lib.resolve ("test"));
            std::stringstream str;
            str << (*realFunc) ();
            QMessageBox::information (& localParent, "Test", QString::fromStdString (str.str ()));
        });
    auto * layout = new QVBoxLayout (result.get ());
    
    layout->addWidget (editor);
    editor->setEntity (literal);
    return std::move (result);
}

/*
Creates a variable_declaration_expression_view in a sandbox_widget container to be shown in the main_window.
*/
std::unique_ptr <omni::forge::sandbox_widget> createVariableDeclarationView (omni::core::context & context, QWidget & parent)
{
    auto variableDecl = std::make_shared <omni::core::model::variable_declaration_expression> ();
    variableDecl->setName ("foobar");
    // For editor and layout, we rely on Qt's object ownership mechanism to free them:
    auto * editor = new omni::ui::variable_declaration_expression_view (context, & parent);
    editor->setEntity (variableDecl);
    auto result = std::make_unique <omni::forge::sandbox_widget> (
        parent,
        [] (omni::core::context &, omni::core::model::module &) -> void {
        });
    auto * layout = new QVBoxLayout (result.get ());
    
    layout->addWidget (editor);
    return std::move (result);
}

/*
Creates an entity_placeholder_widget for the root type omni::core::model::entity, wrapped in a sandbox_widget.
*/
std::unique_ptr <omni::forge::sandbox_widget> createEntityPlaceholderWidget (omni::core::context &, QWidget & parent)
{
    auto result = std::make_unique <omni::forge::sandbox_widget> (
        parent,
        [] (omni::core::context &, omni::core::model::module &) -> void {
        });
    // Relies on Qt's object ownership mechanism to free it:
    auto * placeholderWidget = new omni::ui::entity_placeholder_widget (& parent, omni::core::model::entity::getStaticMetaInfo ());
    auto * layout = new QVBoxLayout (result.get ());
    layout->addWidget (placeholderWidget);
    return std::move (result);
}

/*
Initializes the sandbox tree structure:
*/
std::unique_ptr <omni::forge::sandbox_selector_model::sandbox_selector_data_base> initSandboxData ()
{
    using data_list = std::vector <std::shared_ptr <omni::forge::sandbox_selector_model::sandbox_selector_data_base>>;

    auto result = std::make_unique <sandbox_selector_data <void>> (
        "root",
        "root",
        data_list {
            std::make_shared <sandbox_selector_data <void>> (
                "core",
                "core",
                data_list {
                    std::make_shared <sandbox_selector_data <omni::ui::literal_expression_view>> (
                        "literal_expression",
                        "literal_expression",
                        & createLiteralView),
                    std::make_shared <sandbox_selector_data <omni::ui::variable_declaration_expression_view>> (
                        "variable_declaration_expression",
                        "variable_declaration_expression",
                        & createVariableDeclarationView)
                }),
            std::make_shared <sandbox_selector_data <void>> (
                "ui",
                "ui",
                data_list {
                    std::make_shared <sandbox_selector_data <omni::ui::literal_expression_view>> (
                        "entity_placeholder_widget",
                        "entity_placeholder_widget",
                        & createEntityPlaceholderWidget)
                })
        });
    setParents (* result);
    return std::move (result);
}

}

omni::forge::sandbox_selector_model::sandbox_selector_model (omni::core::context & context) :
    _context (context),
    _root (initSandboxData ())
{
}

omni::forge::sandbox_selector_model::~ sandbox_selector_model ()
{
}

omni::forge::sandbox_widget * omni::forge::sandbox_selector_model::createDemoFromModelIndex (QWidget & parent, const QModelIndex & index)
{
    auto item = reinterpret_cast <sandbox_selector_data_base *> (index.internalPointer ());
    if (item->widget == nullptr) {
        item->widget = item->creator (_context, parent);
    }
    return item->widget.get ();
}

QModelIndex omni::forge::sandbox_selector_model::index (int row, int column, const QModelIndex & parent) const
{

    sandbox_selector_data_base * base;
    if (parent == QModelIndex ()) {
        base = _root.get ();
    } else {
        base = reinterpret_cast <sandbox_selector_data_base *> (parent.internalPointer ());
    }
    switch (static_cast <columns> (column)) {
    case columns::title:
        return createIndex (row, column, base->children [row].get ());
    default:
        throw omni::core::invalid_argument_error (__FILE__, __FUNCTION__, __LINE__, "column", "Invalid column");
    }
    return QModelIndex ();
}

QModelIndex omni::forge::sandbox_selector_model::parent (const QModelIndex & index) const
{
    sandbox_selector_data_base & parent = * reinterpret_cast <sandbox_selector_data_base *> (index.internalPointer ())->parent;
    sandbox_selector_data_base * grandParent = parent.parent;
    if (grandParent == nullptr) {
        return QModelIndex ();
    } else {
        return createIndex (
            std::find_if (
                grandParent->children.begin (),
                grandParent->children.end (),
                [&parent] (std::shared_ptr <sandbox_selector_data_base> & item) -> bool {
                    return item.get () == & parent;
                }) - grandParent->children.begin (),
            index.column (),
            & parent);
    }
}

int omni::forge::sandbox_selector_model::rowCount (const QModelIndex & parent) const
{
    if (parent == QModelIndex ()) {
        return _root->children.size ();
    } else {
        return reinterpret_cast <sandbox_selector_data_base *> (parent.internalPointer ())->children.size ();
    }
}

int omni::forge::sandbox_selector_model::columnCount (const QModelIndex &) const
{
    return 1;
}

QVariant omni::forge::sandbox_selector_model::headerData (int section, Qt::Orientation orientation, int role) const
{
    switch (orientation) {
    case Qt::Horizontal:
        switch (role) {
        case Qt::DisplayRole:
            switch (section) {
            case 0:
                return "Available demos";
            }
            break;
        }
        break;
    }
    return QVariant ();
}

QVariant omni::forge::sandbox_selector_model::data (const QModelIndex & index, int role) const
{
    sandbox_selector_data_base * base;
    if (index == QModelIndex ()) {
        base = _root.get ();
    } else {
        base = reinterpret_cast <sandbox_selector_data_base *> (index.internalPointer ());
    }
    sandbox_selector_data_base & item = * base;//->children [index.row ()];

    switch (role) {
    case Qt::DisplayRole:
        switch (static_cast <columns> (index.column ())) {
        case columns::title:
            return item.title;
        default:
            throw omni::core::invalid_argument_error (__FILE__, __FUNCTION__, __LINE__, "column", "Invalid column");
        }
    default:
        return QVariant ();
        //throw omni::core::invalid_argument_error (__FILE__, __FUNCTION__, __LINE__, "role", "Unsupported role");
    }
}

