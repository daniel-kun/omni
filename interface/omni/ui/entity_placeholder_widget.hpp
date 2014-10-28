#ifndef OMNI_UI_ENTITY_PLACEHOLDER_WIDGET_HPP
#define OMNI_UI_ENTITY_PLACEHOLDER_WIDGET_HPP

#include <omni/ui/ui.hpp>

#include <omni/core/model/meta_info.hpp>

#include <QWidget>
#include <QMenu>

namespace omni {
namespace ui {

/**
@brief entity_placeholder_widget is a placeholder for any entity_base_widget that displays an entity that implements the given entityType.

The entityType is usually a very generic type such as "expression" or "statement". If the entitType is "expression", the entity_placeholder_widget can choose literal_expressions,
variable_assignment_expressions, binary_operator_expressions, and so on. If the entitType is statement, the entity_placeholder_widget can choose blocks, if_statements, 
while_statements, and so on.

TODO: Should the entity_placeholder_widget be permanent and have the chosen entity_base_widget as children, or should the entity_placeholder_widget be deleted after a type has been
chosen and replaced with the entity_base_widget for the given type?
**/
class OMNI_UI_API entity_placeholder_widget : public QWidget {
    Q_OBJECT
public:
    entity_placeholder_widget (QWidget * parent, omni::core::model::meta_info const & entityMeta);

protected:
    void contextMenuEvent (QContextMenuEvent * event) override;

private slots:
    void switchToEntityType ();

private:
    void populateMenu (omni::core::model::meta_info const & meta, QMenu & menu);

    omni::core::model::meta_info const & _entityMeta;
    QMenu _selectorPopup;
};

} // namespace ui
} // namespace omni

#endif // include guard
