#ifndef OMNI_UI_ENTIY_BASE_WIDGET_HPP
#define OMNI_UI_ENTIY_BASE_WIDGET_HPP

#include <omni/ui/ui.hpp>

#include <QWidget>

#include <memory>

namespace omni {
namespace core {
namespace model {
class entity;
}
}
}

namespace omni {
namespace ui {
/**
@brief entity_base_widget is a base class for widgets that display or edit all kinds of non-abstract entities.

Such entities can be omni::core::model::literal_expression s, variable_declaration_expression s, while_statement s and so on.

Compound entities (such as the if_statement, which is a combination of the if-syntax itself, an expression that is the condition and a statement that is the body) have themselves other
entity_base_widget as their children.

The entity that is displayed or edited by an entity_base_widget is access through the methods @see setEntity() and @see getEntity() and stored as a shared_ptr, so that it can be used in
other, unrelated circumstances, too.
**/
class OMNI_UI_API entity_base_widget : public QWidget {
    Q_OBJECT
public:
    entity_base_widget (QWidget * parent);

    virtual std::shared_ptr <omni::core::model::entity> getEntity ();
    virtual void setEntity (std::shared_ptr <omni::core::model::entity> entity);

    virtual void startEdit ();
};

} // namespace ui
} // namespace omni

#endif // include guard
