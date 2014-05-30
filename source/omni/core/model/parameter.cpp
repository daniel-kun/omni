#include <omni/core/model/parameter.hpp>

omni::core::model::parameter::parameter (std::shared_ptr <type> type, std::string name) :
    scope (name),
    _type (type)
{
}

const std::shared_ptr <omni::core::model::type>  omni::core::model::parameter::getType () const
{
    return _type;
}

std::shared_ptr <omni::core::model::type> omni::core::model::parameter::getType ()
{
    return _type;
}
