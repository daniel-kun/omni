#include <omni/core/literal.hpp>
#include <omni/core/type.hpp>

omni::core::literal::literal (std::shared_ptr <type> type) :
    _type (type)
{
    setContext (_type->getContext ());
}

omni::core::literal::~ literal ()
{
}

std::shared_ptr <omni::core::type> omni::core::literal::getType ()
{
    return _type;
}

const std::shared_ptr <omni::core::type> omni::core::literal::getType () const
{
    return _type;
}
