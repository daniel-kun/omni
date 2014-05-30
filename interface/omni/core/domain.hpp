#ifndef OMNI_CORE_DOMAIN_HPP
#define OMNI_CORE_DOMAIN_HPP

#include <omni/core/core.hpp>
#include <ostream>

namespace omni {
namespace core {

    /**
    Every object in the omni context that has an `id' resides in a specific domain to minimize potential id collision and
    to easily see what kind of object is referenced by a specific id. When storing, showing or reading an id the domain should
    always be accompanying the actual id - e.g. as a prefix.
    **/
    enum class domain {
        invalid,
        first,
        binary_operator_expression = first,
        bitcast_expression,
        block,
        builtin_literal,
        do_while_statement,
        expression,
        external_function,
        function,
        function_call_expression,
        if_statement,
        literal,
        literal_expression,
        module,
        parameter,
        return_statement,
        statement,
        type,
        variable_assignment_expression,
        variable_declaration_expression,
        variable_expression,
        while_statement,
        last = while_statement,
    };

    std::ostream OMNI_CORE_API & operator << (std::ostream & lhs, omni::core::domain rhs);

} // namespace core
} // namespace omni

#endif // include guard
