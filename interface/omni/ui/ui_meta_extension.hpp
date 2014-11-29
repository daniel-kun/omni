#ifndef OMNI_UI_UI_META_EXTENSION_HPP
#define OMNI_UI_UI_META_EXTENSION_HPP

#include <omni/ui/ui.hpp>
#include <omni/ui/entity_base_widget.hpp>

#include <omni/core/model/meta_info_extension.hpp>

#include <memory>
#include <functional>

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
@class ui_meta_extension ui_meta_extension.hpp omni/ui/ui_meta_extension.hpp
@brief Holds meta-information for the ui subsystem for every non-abstract omni entity.
**/
class OMNI_UI_API ui_meta_extension : public omni::core::model::meta_info_extension {
public:
    using CreateViewWidgetFunction = std::function <std::unique_ptr <entity_base_widget> (omni::core::context                       & context,
                                                                                          omni::core::model::module                 & module,
                                                                                          QWidget                                   * parent,
                                                                                          std::shared_ptr <omni::core::model::entity> entity)>;

    ui_meta_extension (CreateViewWidgetFunction viewWidgetCreator);

    std::unique_ptr <entity_base_widget> createViewWidget (omni::core::context                       & context,
                                                           omni::core::model::module                 & module,
                                                           QWidget                                   * parent,
                                                           std::shared_ptr <omni::core::model::entity> entity) const;

private:
    CreateViewWidgetFunction _viewWidgetCreator;
};

} // namespace ui
} // namespace omni

#endif // include guard
