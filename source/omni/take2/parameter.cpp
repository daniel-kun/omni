#include <omni/take2/parameter.hpp>

omni::take2::parameter::parameter (std::shared_ptr <type> type, std::string name) :
    _type (type),
    _name (name)
{
}

const omni::take2::type & omni::take2::parameter::getType () const
{
    return * _type;
}

omni::take2::type & omni::take2::parameter::getType ()
{
    return * _type;
}
