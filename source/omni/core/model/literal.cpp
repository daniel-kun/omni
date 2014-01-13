#include <omni/core/model/literal.hpp>
#include <omni/core/model/type.hpp>

omni::core::model::literal::literal (std::shared_ptr <type> type) :
    _type (type)
{
    setContext (_type->getContext ());
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
