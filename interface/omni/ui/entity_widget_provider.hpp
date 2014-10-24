#ifndef OMNI_UI_ENTITY_WIDGET_PROVIDER_HPP
#define OMNI_UI_ENTITY_WIDGET_PROVIDER_HPP

#include <omni/ui/ui.hpp>
#include <omni/ui/entity_widget_provider_base.hpp>

#include <QWidget>
#include <QKeyEvent>

#include <functional>
#include <string>
#include <memory>

namespace omni {
namespace core {
class context;
}
}

namespace omni {
namespace ui {
class entity_base_widget;

/**
@brief Creates edit- and view-widgets for a specific type of entity.


**/
class OMNI_UI_API entity_widget_provider : public entity_widget_provider_base {
public:
    static entity_widget_provider & getProvider (std::string entityType);

    entity_widget_provider (
        std::function <std::unique_ptr <omni::ui::entity_base_widget> (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget * editWidget)> viewCreator,
        std::function <std::unique_ptr <omni::ui::entity_base_widget> (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget & viewWidget)> editCreator,
        std::function <bool (QKeyEvent * event)> keyHandler);

    std::unique_ptr <omni::ui::entity_base_widget> createViewWidget (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget * editWidget) override;
    std::unique_ptr <omni::ui::entity_base_widget> createEditWidget (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget & viewWidget) override;
    bool keyPressEvent (QKeyEvent * event) override;

private:
    std::function <std::unique_ptr <omni::ui::entity_base_widget> (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget * editWidget)> _viewCreator;
    std::function <std::unique_ptr <omni::ui::entity_base_widget> (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget & viewWidget)> _editCreator;
    std::function <bool (QKeyEvent * event)> _keyHandler;
};

} // namespace ui
} // namespace omni

#endif // include guard
