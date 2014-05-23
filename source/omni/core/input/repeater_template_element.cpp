#include <omni/core/input/repeater_template_element.hpp>
#include <omni/core/input/template_visitor.hpp>

void omni::core::input::repeater_template_element::visit (template_visitor & visitor)
{
    visitor.visitRepeaterTemplateElement (* this);
}
