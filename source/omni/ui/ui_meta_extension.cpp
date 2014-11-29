#include <omni/ui/ui_meta_extension.hpp>

/**
@brief Initializes this ui_meta_extension with the given parameters.
@param viewWidgetCreator This function will be used in createViewWidget() to return a new widget for an entity of the type corresponding to the meta_info that this
extension is attached to.
**/
omni::ui::ui_meta_extension::ui_meta_extension (CreateViewWidgetFunction viewWidgetCreator) :
    _viewWidgetCreator (viewWidgetCreator)
{
}

/**
@brief Returns a new widget for an entity of the type corresponding to the meta_info that this extension is attached to.
@return A new widget for an entity of the type corresponding to the meta_info that this extension is attached to.
**/
std::unique_ptr <omni::ui::entity_base_widget> omni::ui::ui_meta_extension::createViewWidget (omni::core::context                       & context,
                                                                                              omni::core::model::module                 & module,
                                                                                              QWidget                                   * parent,
                                                                                              std::shared_ptr <omni::core::model::entity> entity) const
{
    return _viewWidgetCreator (context, module, parent, entity);
}
