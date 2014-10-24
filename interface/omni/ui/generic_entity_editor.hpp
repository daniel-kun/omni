#ifndef OMNI_UI_GENERIC_ENTITY_EDITOR_HPP
#define OMNI_UI_GENERIC_ENTITY_EDITOR_HPP

#include <omni/ui/entity_base_widget.hpp>

#include <QStackedLayout>
#include <QLineEdit>

#include <memory>
#include <functional>

namespace omni {
namespace ui {

/**
@brief generic_entity_editor can be used directly or as a base class for simple entity editors that use a QLineEdit to edit the entity.

generic_entity_editor uses the entity's toString() method (with fullyQualified set to false) or the provided textToEntityConverter (@see setEntityToTextConverter())to form an editable text from the entity.
Converting a text to an entity is less generic, so it requires an text-to-entity-converter to be set via @see setTextToEntityConverter().

Auto-completion and other editing aids are yet to be implemented.

The generic_entity_editor has it's focus proxy set to a QLineEdit that is it's sole child widget, without margins or paddings. That way, generic_entity_editor behaves like it was a 
QLineEdit itself.
**/
class OMNI_UI_API generic_entity_editor : public entity_base_widget {
    Q_OBJECT
public:
    generic_entity_editor (QWidget * parent, std::shared_ptr <omni::core::model::entity> entity = std::shared_ptr <omni::core::model::entity> ());

    std::function <std::string (std::shared_ptr <omni::core::model::entity>)> getEntityToTextConverter () const;
    void setEntityToTextConverter (std::function <std::string (std::shared_ptr <omni::core::model::entity>)> converter);

    std::function <std::shared_ptr <omni::core::model::entity> (std::string text, std::shared_ptr <omni::core::model::entity> originatingEntity)> getTextToEntityConverter () const;
    void setTextToEntityConverter (std::function <std::shared_ptr <omni::core::model::entity> (std::string text, std::shared_ptr <omni::core::model::entity> originatingEntity)> converter);

    std::shared_ptr <omni::core::model::entity> getEntity () override;
    void setEntity (std::shared_ptr <omni::core::model::entity> entity) override;

private:
    std::function <std::string (std::shared_ptr <omni::core::model::entity>)> _entityToTextConverter;
    std::function <std::shared_ptr <omni::core::model::entity> (std::string text, std::shared_ptr <omni::core::model::entity> originatingEntity)> _textToEntityConverter;
    std::shared_ptr <omni::core::model::entity> _entity;
    QStackedLayout _layout;
    QLineEdit _edit;
};

}
}

#endif // include guard
