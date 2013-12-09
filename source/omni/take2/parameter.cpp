#include <omni/take2/parameter.hpp>

omni::take2::parameter::parameter (std::shared_ptr <type> type, std::string name) :
    _type (type),
    _name (name)
{
}

const std::shared_ptr <omni::take2::type>  omni::take2::parameter::getType () const
{
    return _type;
}

std::shared_ptr <omni::take2::type> omni::take2::parameter::getType ()
{
    return _type;
}
