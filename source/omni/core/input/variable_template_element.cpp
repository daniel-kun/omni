#include <omni/core/input/variable_template_element.hpp>
#include <omni/core/input/variable_template_provider.hpp>

omni::core::input::variable_template_element::variable_template_element (
    syntax_element & parent,
    std::size_t templateIndex,
    variable_template_provider & provider) :
    template_element (parent, templateIndex),
    _provider        (provider)
{
}

std::vector <std::string> omni::core::input::variable_template_element::suggest (std::string input)
{
    return _provider.provide (input);
}
