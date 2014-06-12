#include <omni/core/model/literal.hpp>
#include <omni/core/model/type.hpp>

/**
@brief Initializes a literal of the given type.

Since this class is abstract, the type is not really used. It is up to the classes implementing actual literals to
use and manage the type.
@param literalType The type of the value that this literal represents.
@see getType
**/
omni::core::model::literal::literal (std::shared_ptr <type> literalType = std::shared_ptr <type> ()) :
    scope (),
    _type (literalType)
{
}

omni::core::model::literal::~ literal ()
{
}

/**
@brief Returns the type of the value that this literal represents.

The returned type can be modified.

@return The type of the value that this literal represents.
**/
std::shared_ptr <omni::core::model::type> omni::core::model::literal::getType ()
{
    return _type;
}

/**
@brief Returns the type of the value that this literal represents.

The returned type is const and can not be modified.

@return The type of the value that this literal represents.
**/
const std::shared_ptr <omni::core::model::type> omni::core::model::literal::getType () const
{
    return _type;
}
