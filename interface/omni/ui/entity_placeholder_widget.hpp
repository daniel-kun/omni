#ifndef OMNI_UI_ENTITY_PLACEHOLDER_WIDGET_HPP
#define OMNI_UI_ENTITY_PLACEHOLDER_WIDGET_HPP

#include <omni/ui/ui.hpp>
#include <omni/ui/entity_base_widget.hpp>

#include <omni/core/model/meta_info.hpp>

#ifndef Q_MOC_RUN
#include <boost/signals2.hpp>
#endif

#include <QWidget>
#include <QMenu>
#include <QHBoxLayout>
#include <QLineEdit>

namespace omni {
namespace core {
class context;

namespace model {
class module;
}
}
}

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
    using on_entity_expanded_signal = boost::signals2::signal <void (std::shared_ptr <omni::core::model::entity>)>;
    
    entity_placeholder_widget (omni::core::context & context, omni::core::model::module & module, QWidget * parent, omni::core::model::meta_info const & entityMeta);

    on_entity_expanded_signal onEntityExpanded;

protected:
    void contextMenuEvent (QContextMenuEvent * event) override;

private slots:
    void switchToEntityType ();
    void editorTextChanged (const QString & text);

private:
    void populateMenu (omni::core::model::meta_info const & meta, QMenu & menu);
    void createEditorViewFromMetaInfo (const omni::core::model::meta_info & metaInfo, std::shared_ptr <omni::core::model::entity> entity);

    omni::core::context & _context;
    omni::core::model::module & _module;
    omni::core::model::meta_info const & _entityMeta;
    QMenu _selectorPopup;
    QHBoxLayout _layout;
    QLineEdit _editor;
    std::unique_ptr <entity_base_widget> _entityWidget;
};

} // namespace ui
} // namespace omni

#endif // include guard
