#include <omni/ui/generic_entity_editor.hpp>
#include <omni/core/model/literal_expression.hpp>

omni::ui::generic_entity_editor::generic_entity_editor (QWidget * parent, std::shared_ptr <omni::core::model::entity> entity) :
    entity_base_widget (parent),
    _entityToTextConverter (),
    _textToEntityConverter (),
    _entity (entity),
    _layout (this),
    _edit (this)
{
    _layout.addWidget (& _edit);
    setFocusProxy (& _edit);
}

std::function <std::string (std::shared_ptr <omni::core::model::entity>)> omni::ui::generic_entity_editor::getEntityToTextConverter () const
{
    return _entityToTextConverter;
}

void omni::ui::generic_entity_editor::setEntityToTextConverter (std::function <std::string (std::shared_ptr <omni::core::model::entity>)> converter)
{
    _entityToTextConverter = converter;
}

std::function <std::shared_ptr <omni::core::model::entity> (std::string text, std::shared_ptr <omni::core::model::entity> originatingEntity)> omni::ui::generic_entity_editor::getTextToEntityConverter () const
{
    return _textToEntityConverter;
}

void omni::ui::generic_entity_editor::setTextToEntityConverter (std::function <std::shared_ptr <omni::core::model::entity> (std::string text, std::shared_ptr <omni::core::model::entity> originatingEntity)> converter)
{
    _textToEntityConverter = converter;
}

std::shared_ptr <omni::core::model::entity> omni::ui::generic_entity_editor::getEntity ()
{
    if (_textToEntityConverter) {
        return _textToEntityConverter (_edit.text ().toStdString (), _entity);
    } else {
        return _entity;
    }
}

void omni::ui::generic_entity_editor::setEntity (std::shared_ptr <omni::core::model::entity> entity)
{
    _entity = entity;
    if (_entityToTextConverter) {
        _edit.setText (QString::fromStdString (_entityToTextConverter (entity)));
    } else {
        // TODO: This is only for tests, toString needs to be added to omni::core::model::entity:
        auto literal = std::dynamic_pointer_cast <omni::core::model::literal_expression> (entity);
        _edit.setText (QString::fromStdString (literal->toString (false)));
    }
}
