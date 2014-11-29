#include <omni/ui/entity_placeholder_widget.hpp>
#include <omni/core/parser.hpp>
#include <omni/core/model/module.hpp>
#include <omni/ui/ui_meta_extension.hpp>
#include <omni/ui/entity_base_widget.hpp>

#include <omni/core/model/entity.hpp>

#include <QContextMenuEvent>
#include <QMessageBox>
#include <QStringBuilder>

namespace {

/**
@brief Enriches an QAction object with a reference to a meta_info.
**/    
class meta_action : public QAction {
public:
    meta_action (const omni::core::model::meta_info & metaInfo, const QString & text, QObject * parent);

    const omni::core::model::meta_info & getMetaInfo ();

private:
    const omni::core::model::meta_info & _metaInfo;
};


meta_action::meta_action (const omni::core::model::meta_info & metaInfo, const QString & text, QObject * parent) :
    QAction (text, parent),
    _metaInfo (metaInfo)
{
}

const omni::core::model::meta_info & meta_action::getMetaInfo ()
{
    return _metaInfo;
}

}

omni::ui::entity_placeholder_widget::entity_placeholder_widget (
    omni::core::context & context,
    omni::core::model::module & module,
    QWidget * parent,
    omni::core::model::meta_info const & entityMeta) :

    QWidget (parent),
    _context (context),
    _module (module),
    _entityMeta (entityMeta),
    _selectorPopup (this),
    _layout (this),
    _editor (this),
    _entityWidget ()
{
    _layout.addWidget (& _editor);
    connect (& _editor, & QLineEdit::textChanged, this, & entity_placeholder_widget::editorTextChanged);

    setMinimumSize (100, 100);
    setAutoFillBackground (true);
    QPalette pal = palette ();
    pal.setBrush (QPalette::Background, Qt::gray);
    setPalette (pal);
}

void omni::ui::entity_placeholder_widget::contextMenuEvent (QContextMenuEvent * event)
{
    _selectorPopup.clear ();
    populateMenu (_entityMeta, _selectorPopup);
    _selectorPopup.popup (QPoint (event->globalX (), event->globalY ()));
}

void omni::ui::entity_placeholder_widget::switchToEntityType ()
{
    auto * action = dynamic_cast <meta_action *> (sender ());
    createEditorViewFromMetaInfo (action->getMetaInfo (), std::unique_ptr <omni::core::model::entity> ());
}

void omni::ui::entity_placeholder_widget::populateMenu (omni::core::model::meta_info const & meta, QMenu & menu)
{
    if (! meta.isAbstract ()) {
        auto * action = new meta_action (meta, QString::fromStdString (meta.getName ()), & menu);
        connect (action, SIGNAL(triggered()), SLOT(switchToEntityType()));
        menu.addAction (action);
    }
    for (std::size_t i = 0u; i < meta.getChildCount (); ++ i) {
        auto & child = meta.getChildAt (i);
        populateMenu (child, menu);
    }
}

void omni::ui::entity_placeholder_widget::editorTextChanged (const QString & text)
{
    omni::core::parser::StatementList statements = omni::core::parser::parseStatement (_module, text.toStdString ());
    if (statements.size () == 1u) {
        std::shared_ptr <omni::core::model::statement> statement = statements [0].entity;
        createEditorViewFromMetaInfo (statement->getMetaInfo (), statement);
    }
}

void omni::ui::entity_placeholder_widget::createEditorViewFromMetaInfo (const omni::core::model::meta_info & metaInfo,
                                                                        std::shared_ptr <omni::core::model::entity> entity)
{
    const auto & uiExtension = * dynamic_cast <const ui_meta_extension *> (metaInfo.getExtension ("omni.ui"));
    _entityWidget = uiExtension.createViewWidget (_context, _module, this, entity);
    _editor.hide ();
    _layout.addWidget (_entityWidget.get ());
    _entityWidget->startEdit ();

    onEntityExpanded (_entityWidget->getEntity ());
}
