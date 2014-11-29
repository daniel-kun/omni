#include <omni/ui/entity_base_widget.hpp>

omni::ui::entity_base_widget::entity_base_widget (QWidget * parent) :
    QWidget (parent)
{
}

std::shared_ptr <omni::core::model::entity> omni::ui::entity_base_widget::getEntity ()
{
    return std::shared_ptr <omni::core::model::entity> ();
}

void omni::ui::entity_base_widget::setEntity (std::shared_ptr <omni::core::model::entity> entity)
{
    // nop
}

/**
@brief Called after entity_placeholder_widget has been completed to this entity_base_widget and this widget needs to be put into editing mode to continue typing.
**/
void omni::ui::entity_base_widget::startEdit ()
{

}

