#include <omni/ui/variable_declaration_expression_view.hpp>
#include <omni/ui/generic_entity_editor.hpp>
#include <omni/core/invalid_argument_error.hpp>

namespace {

class variable_name_view_widget : public omni::ui::entity_base_widget {
public:
    variable_name_view_widget (QWidget * parent) :
        entity_base_widget (parent),
        _layout (this),
        _label (this),
        _variableDecl ()
    {
        _layout.addWidget (& _label);
    }

    std::shared_ptr <omni::core::model::entity> getEntity ()
    {
        return _variableDecl;    
    }

    void setEntity (std::shared_ptr <omni::core::model::entity> entity)
    {
        _variableDecl = std::dynamic_pointer_cast <omni::core::model::variable_declaration_expression> (entity);
        if (!_variableDecl) {
            throw omni::core::invalid_argument_error (__FILE__, __FUNCTION__, __LINE__, "entity", "Not of type variable_declaration_expression or null");
        }
        _label.setText (QString::fromStdString (_variableDecl->getName ()));
    }

private:
    QHBoxLayout _layout;
    QLabel _label;
    std::shared_ptr <omni::core::model::variable_declaration_expression> _variableDecl;
};

class variable_name_edit_provider : public omni::ui::entity_widget_provider_base {
public:
    std::unique_ptr <omni::ui::entity_base_widget> createViewWidget (QWidget * parent, omni::core::context &, omni::ui::entity_base_widget * editWidget) override
    {
        auto result = std::unique_ptr <variable_name_view_widget> (new variable_name_view_widget (parent));
        if (editWidget != nullptr) {
            result->setEntity (editWidget->getEntity ());
        }
        return std::move (result);
    }
    
    std::unique_ptr <omni::ui::entity_base_widget> createEditWidget (QWidget * parent, omni::core::context &, omni::ui::entity_base_widget & viewWidget) override
    {
        auto result = std::unique_ptr <omni::ui::generic_entity_editor> (new omni::ui::generic_entity_editor (parent));
        result->setEntityToTextConverter (
            [] (std::shared_ptr <omni::core::model::entity> originatingEntity) -> std::string {
                return originatingEntity->getName ();
            });
        result->setTextToEntityConverter (
            [] (std::string text, std::shared_ptr <omni::core::model::entity> originatingEntity) -> std::shared_ptr <omni::core::model::entity> {
                auto variableDecl = std::dynamic_pointer_cast <omni::core::model::variable_declaration_expression> (originatingEntity);
                if (! variableDecl) {
                    throw omni::core::invalid_argument_error (__FILE__, __FUNCTION__, __LINE__, "entity", "Can't convert text to entity. Not of type variable_declaration_expression or null");
                }
                variableDecl->setName (text);
                return variableDecl;
            });
        result->setEntity (viewWidget.getEntity ());
        return std::move (result);
    }
    
    bool keyPressEvent (QKeyEvent * ) override
    {
        return false;
    }
};
}

omni::ui::variable_declaration_expression_view::variable_declaration_expression_view (omni::core::context & context, omni::core::model::module & module, QWidget * parent) :
    entity_base_widget (parent),
    _layout (this),
    _varFixedText (this),
    _nameWidgetProvider (std::unique_ptr <variable_name_edit_provider> (new variable_name_edit_provider ())),
    _nameWidget (context, * _nameWidgetProvider, this),
    _assignmentOperator (this),
    _initializationExpression (context, module, this, omni::core::model::expression::getStaticMetaInfo ()),
    _variableDeclExpression (),
    _initExpressionExpandedConnection (_initializationExpression.onEntityExpanded.connect ([this] (std::shared_ptr <omni::core::model::entity> entity) -> void { updateInitializationExpression (entity); }))
{
    _layout.addWidget (& _varFixedText, 0, Qt::AlignLeft);
    _layout.addWidget (& _nameWidget, 0, Qt::AlignLeft);
    _layout.addWidget (& _assignmentOperator, 0, Qt::AlignLeft);
    _layout.addWidget (& _initializationExpression, 1, Qt::AlignLeft);
    _varFixedText.setText ("var ");
    _assignmentOperator.setText (" = ");
    setAutoFillBackground (true);
    auto pal = palette ();
    pal.setBrush (QPalette::Background, QBrush (QColor (128, 73, 255)));
    setPalette (pal);
}

std::shared_ptr <omni::core::model::entity> omni::ui::variable_declaration_expression_view::getEntity ()
{
    return _variableDeclExpression;
}

void omni::ui::variable_declaration_expression_view::setEntity (std::shared_ptr <omni::core::model::entity> entity)
{
    _variableDeclExpression = std::dynamic_pointer_cast <omni::core::model::variable_declaration_expression> (entity);
    if (!_variableDeclExpression) {
        throw omni::core::invalid_argument_error (__FILE__, __FUNCTION__, __LINE__, "entity", "Not of type variable_declaration_expression or null");
    }
    _nameWidget.setEntity (entity);
}

void omni::ui::variable_declaration_expression_view::startEdit ()
{
    if (_nameWidget.currentViewMode () != omni::ui::entity_toggle_widget::Mode::m_edit) {
        _nameWidget.toggleViewMode ();
        _nameWidget.setFocus (Qt::TabFocusReason);
    }
}

void omni::ui::variable_declaration_expression_view::updateInitializationExpression (std::shared_ptr <omni::core::model::entity> initializationExpression)
{
    auto initExpr = std::dynamic_pointer_cast <omni::core::model::expression> (initializationExpression);
    if (!initExpr) {
        throw omni::core::invalid_argument_error (__FILE__, __FUNCTION__, __LINE__, "initializationExpression", "Not of type expression or null");
    }
    _variableDeclExpression->setInitializationExpression (initExpr);
}
