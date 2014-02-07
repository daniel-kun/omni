#include <omni/core/input/template_element.hpp>

omni::core::input::template_element::template_element (
    syntax_element & parent,
    std::size_t templateIndex) :
    _parent        (parent),
    _templateIndex (templateIndex)
{
}

/**
If this template_element contains a syntax_element in some form, return that syntax_element.
If this template_element is not a placeholder for a syntax_element, nullptr is returned.
**/
std::shared_ptr <omni::core::input::syntax_element> omni::core::input::template_element::dive ()
{
    return nullptr;
}
