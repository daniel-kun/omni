#ifndef OMNI_CORE_TEMPLATE_VARIABLES_HPP
#define OMNI_CORE_TEMPLATE_VARIABLES_HPP

namespace omni {
namespace core {
namespace input {

/**
**/
enum class template_variables {
    /**
    A variable's name can be inserted in this place. Used in variable_expression and variable_assignment_expression.
    **/
    variable,
    /**
    A function's name can be inserted in this place. Used in function_call_expression.
    **/
    function,
    /**
    A plus or a minus sign can be inserted in this place. Used in literal_expression for numeric literals.
    **/
    numeric_sign,
    /**
    An binary operator can be inserted in this place. Used in binary_operator_expression.
    **/
    binary_operator
};

} // namespace input
} // namespace core
} // namespace omni

#endif // include guard
