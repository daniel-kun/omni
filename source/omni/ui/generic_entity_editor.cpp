#include <omni/ui/generic_entity_editor.hpp>
#include <omni/core/model/literal_expression.hpp>

omni::ui::generic_entity_editor::generic_entity_editor (QWidget * parent, std::shared_ptr <omni::core::model::entity> entity) :
    entity_base_widget (parent),
    _entity (entity),
    _layout (this),
    _edit (this)
{
    _layout.addWidget (& _edit);
    setFocusProxy (& _edit);
}

std::function <std::shared_ptr <omni::core::model::entity> (std::string text, std::shared_ptr <omni::core::model::entity> originatingEntity)> omni::ui::generic_entity_editor::getTextToEntityConverter ()
{
    return _converter;
}

void omni::ui::generic_entity_editor::setTextToEntityConverter (std::function <std::shared_ptr <omni::core::model::entity> (std::string text, std::shared_ptr <omni::core::model::entity> originatingEntity)> converter)
{
    _converter = converter;
}

std::shared_ptr <omni::core::model::entity> omni::ui::generic_entity_editor::getEntity ()
{
    if (_converter) {
        return _converter (_edit.text ().toStdString (), _entity);
    } else {
        return _entity;
    }
}

void omni::ui::generic_entity_editor::setEntity (std::shared_ptr <omni::core::model::entity> entity)
{
    _entity = entity;
    auto literal = std::dynamic_pointer_cast <omni::core::model::literal_expression> (entity);
    _edit.setText (QString::fromStdString (literal->toString (false)));
}
