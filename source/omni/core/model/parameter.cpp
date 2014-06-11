#include <omni/core/model/parameter.hpp>

/**
@brief Initializes this parameter with the given type and name.
The name can be changed later using entity::setName().
The type can be set or changed later using setType ().
**/
omni::core::model::parameter::parameter (std::shared_ptr <type> type, std::string name) :
    scope (name),
    _type (type)
{
}

omni::core::domain omni::core::model::parameter::getDomain () const
{
    return domain::parameter;
}

/**
@brief Changes the type of this parameter.

Changing the type means that possible function_call_expression s will no longer be valid, because the types might
not match the new type.
@param type The new type that this parameter should have.
@see getType
**/
void omni::core::model::parameter::setType (std::shared_ptr <type> type)
{
}

/**
@brief Returns the type of this parameter.

The type of a parameter specifies which kind of expressions can be passed when calling the function using function_call_expression.

The expressions passed to function_call_expression::appendParameter or function_call_expression::setParameters have to match the
order and exact types of the parameters set in function_prototype::function_prototype, function_prototype::appendParameter or
function_prototype::setParameters.

@return The type of this parameter. The returned type is const and can not be modified.
**/
const std::shared_ptr <omni::core::model::type>  omni::core::model::parameter::getType () const
{
    return _type;
}

/**
@brief Returns the type of this parameter.

The type of a parameter specifies which kind of expressions can be passed when calling the function using function_call_expression.

The expressions passed to function_call_expression::appendParameter or function_call_expression::setParameters have to match the
order and exact types of the parameters set in function_prototype::function_prototype, function_prototype::appendParameter or
function_prototype::setParameters.

@return The type of this parameter. The returned type can be modified.
**/
std::shared_ptr <omni::core::model::type> omni::core::model::parameter::getType()
{
    return _type;
}
