#include <omni/core/model/literal.hpp>
#include <omni/core/model/type.hpp>

omni::core::model::literal::literal (omni::core::model::scope & parent, std::shared_ptr <type> type) :
    scope (& parent),
    _type (type)
{
}

omni::core::model::literal::~ literal ()
{
}

std::shared_ptr <omni::core::model::type> omni::core::model::literal::getType ()
{
    return _type;
}

const std::shared_ptr <omni::core::model::type> omni::core::model::literal::getType () const
{
    return _type;
}
