#include <omni/core/domain.hpp>

#include <boost/format.hpp>

std::ostream & omni::core::operator << (std::ostream & lhs, omni::core::domain rhs)
{
    switch (rhs) {
    case omni::core::domain::invalid:
        lhs << "invalid";
        break;
    case omni::core::domain::binary_operator_expression:
        lhs << "binary_operator_expression";
        break;
    case omni::core::domain::bitcast_expression:
        lhs << "bitcast_expression";
        break;
    case omni::core::domain::block:
        lhs << "block";
        break;
    case omni::core::domain::do_while_statement:
        lhs << "do_while_statement";
        break;
    case omni::core::domain::expression:
        lhs << "expression";
        break;
    case omni::core::domain::external_function:
        lhs << "external_function";
        break;
    case omni::core::domain::function:
        lhs << "function";
        break;
    case omni::core::domain::function_call_expression:
        lhs << "function_call_expression";
        break;
    case omni::core::domain::if_statement:
        lhs << "if_statement";
        break;
    case omni::core::domain::builtin_literal_expression:
        lhs << "builtin_literal_expression";
        break;
    case omni::core::domain::module:
        lhs << "module";
        break;
    case omni::core::domain::parameter:
        lhs << "parameter";
        break;
    case omni::core::domain::return_statement:
        lhs << "return_statement";
        break;
    case omni::core::domain::statement:
        lhs << "statement";
        break;
    case omni::core::domain::type:
        lhs << "type";
        break;
    case omni::core::domain::variable_assignment_expression:
        lhs << "variable_assignment_expression";
        break;
    case omni::core::domain::variable_declaration_expression:
        lhs << "variable_declaration_expression";
        break;
    case omni::core::domain::variable_expression:
        lhs << "variable_expression";
        break;
    case omni::core::domain::while_statement:
        lhs << "while_statement";
        break;
    default:
        throw std::runtime_error ((boost::format ("Can not stream unknown domain %1% to std::ostream") % static_cast <std::size_t> (rhs)).str ());
    }
    return lhs;
}
