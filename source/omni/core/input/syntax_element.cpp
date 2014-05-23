#include <omni/core/input/syntax_element.hpp>

void omni::core::input::syntax_element::setName (std::string const & name)
{
    _name = name;
}

std::string omni::core::input::syntax_element::getName () const
{
    return _name;
}

std::shared_ptr <omni::core::input::template_element> omni::core::input::syntax_element::templateElementAt (std::size_t templatePosition)
{
    return nullptr;
}

std::size_t omni::core::input::syntax_element::templateElementCount () const
{
    return 0u;
}
