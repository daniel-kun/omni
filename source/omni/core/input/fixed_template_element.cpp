#include <omni/core/input/fixed_template_element.hpp>

omni::core::input::fixed_template_element::fixed_template_element (syntax_element & parent, std::size_t templateIndex, std::string text):
    template_element (parent, templateIndex),
    _text            (text)
{
}

std::vector <std::string> omni::core::input::fixed_template_element::suggest (std::string input)
{
    if (_text.find (input) == 0u) {
        return std::vector <std::string> {
            _text
        };
    } else {
        return std::vector <std::string> ();
    }
}
