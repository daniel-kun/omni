#ifndef OMNI_UI_ENTITY_WIDGET_PROVIDER_BASE_HPP
#define OMNI_UI_ENTITY_WIDGET_PROVIDER_BASE_HPP

#include <omni/ui/ui.hpp>

#include <QWidget>
#include <QKeyEvent>

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
@brief Abstract interface to create edit- and view-widgets.
**/
class OMNI_UI_API entity_widget_provider_base {
public:
    virtual std::unique_ptr <omni::ui::entity_base_widget> createViewWidget (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget * editWidget) = 0;
    virtual std::unique_ptr <omni::ui::entity_base_widget> createEditWidget (QWidget * parent, omni::core::context & context, omni::ui::entity_base_widget & viewWidget) = 0;
    virtual bool keyPressEvent (QKeyEvent * event) = 0;
};

} // namespace ui
} // namespace omni

#endif // include guard
