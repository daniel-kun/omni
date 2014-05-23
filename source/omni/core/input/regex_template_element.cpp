#include <omni/core/input/regex_template_element.hpp>
#include <omni/core/input/template_visitor.hpp>

void omni::core::input::regex_template_element::visit (template_visitor & visitor)
{
    visitor.visitRegexTemplateElement (* this);
}
