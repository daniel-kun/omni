#ifndef OMNI_CORE_MODIFYING_EXPRESSION_HPP
#define OMNI_CORE_MODIFYING_EXPRESSION_HPP

#include <omni/core/core.hpp>
#include <omni/core/expression.hpp>

namespace omni {
namespace core {

    /**
    An modifying_expression is an expression that does modify at least one of it's operands or has side-effects.
    A modifying_expression does not have any special functionality or properties, it is just a kind of a class of expressions.
    @see pure_expression
    **/
    class OMNI_CORE_API modifying_expression : public expression {
    public:
    };

} // namespace core
} // namespace omni

#endif // include guard
