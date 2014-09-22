#include <omni/ui/entity_widget_provider.hpp>
#include <omni/ui/entity_base_widget.hpp>
#include <omni/ui/literal_expression_view.hpp>
#include <omni/ui/generic_entity_editor.hpp>

#include <omni/core/invalid_argument_error.hpp>
#include <omni/core/model/literal_expression.hpp>

std::map <std::string, omni::ui::entity_widget_provider> s_widgetProviderRegistry = {
        { "literal_expression", omni::ui::entity_widget_provider (
            [] (QWidget * parent, omni::core::context &, omni::ui::entity_base_widget * editWidget) -> std::unique_ptr <omni::ui::entity_base_widget> {
                std::shared_ptr <omni::core::model::literal_expression> literal;
                if (editWidget != nullptr) {
                    literal = std::dynamic_pointer_cast <omni::core::model::literal_expression> (editWidget->getEntity ());
                }
                auto viewWidget = std::make_unique <omni::ui::literal_expression_view> (parent);
                viewWidget->setLiteral (literal);
                return std::move (viewWidget);
            },
            [] (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget & viewWidget) -> std::unique_ptr <omni::ui::entity_base_widget> {
                auto result = std::make_unique <omni::ui::generic_entity_editor> (parent, viewWidget.getEntity ());
                result->setTextToEntityConverter ([&context] (std::string text, std::shared_ptr <omni::core::model::entity> originatingEntity) -> std::shared_ptr <omni::core::model::entity> {
                    auto literal = std::dynamic_pointer_cast <omni::core::model::literal_expression> (originatingEntity);
                    return omni::core::model::literal_expression::fromString (context, text, literal.get ());
                });
                result->setEntity (viewWidget.getEntity ());
                return std::move (result);
            },
            std::function <bool (QKeyEvent * event)> ())
        }
};

omni::ui::entity_widget_provider & omni::ui::entity_widget_provider::getProvider (std::string entityType)
{
    auto iterator = s_widgetProviderRegistry.find (entityType);
    if (iterator != s_widgetProviderRegistry.end ()) {
        return iterator->second;
    } else {
        throw omni::core::invalid_argument_error (__FILE__, __FUNCTION__, __LINE__, "entityType", "An entity \"" + entityType + "\" was not found.");
    }
}

/*
std::unique_ptr <omni::ui::entity_base_widget> omni::ui::entity_widget_provider::createViewWidget (std::string entityType, QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget * editWidget)
{
    auto iterator = s_widgetProviderRegistry.find (entityType);
    if (iterator != s_widgetProviderRegistry.end ()) {
        return iterator->second.createViewWidget (parent, context, editWidget);
    } else {
        throw omni::core::invalid_argument_error (__FILE__, __FUNCTION__, __LINE__, "entityType", "An entity \"" + entityType + "\" was not found.");
    }
}

std::unique_ptr <omni::ui::entity_base_widget> omni::ui::entity_widget_provider::createEditWidget (std::string entityType, QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget & viewWidget)
{
    auto iterator = s_widgetProviderRegistry.find (entityType);
    if (iterator != s_widgetProviderRegistry.end ()) {
        return iterator->second.createEditWidget (parent, context, viewWidget);
    } else {
        throw omni::core::invalid_argument_error (__FILE__, __FUNCTION__, __LINE__, "entityType", "An entity \"" + entityType + "\" was not found.");
    }
}
*/

omni::ui::entity_widget_provider::entity_widget_provider (
    std::function <std::unique_ptr <omni::ui::entity_base_widget> (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget * editWidget)> viewCreator,
    std::function <std::unique_ptr <omni::ui::entity_base_widget> (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget & viewWidget)> editCreator,
    std::function <bool (QKeyEvent * event)> keyHandler) :
    _viewCreator (viewCreator),
    _editCreator (editCreator),
    _keyHandler (keyHandler)
{
}
                                                                
std::unique_ptr <omni::ui::entity_base_widget> omni::ui::entity_widget_provider::createViewWidget (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget * editWidget)
{
    return _viewCreator (parent, context, editWidget);
}

std::unique_ptr <omni::ui::entity_base_widget> omni::ui::entity_widget_provider::createEditWidget (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget & viewWidget)
{
    return _editCreator (parent, context, viewWidget);
}

bool omni::ui::entity_widget_provider::keyPressEvent (QKeyEvent * event)
{
    return _keyHandler (event);
}


