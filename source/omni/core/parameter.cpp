#include <omni/core/parameter.hpp>

omni::core::parameter::parameter (std::shared_ptr <type> type, std::string name) :
    _type (type),
    _name (name)
{
}

const std::shared_ptr <omni::core::type>  omni::core::parameter::getType () const
{
    return _type;
}

std::shared_ptr <omni::core::type> omni::core::parameter::getType ()
{
    return _type;
}
