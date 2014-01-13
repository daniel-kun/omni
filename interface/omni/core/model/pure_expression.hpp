#ifndef OMNI_CORE_PURE_EXPRESSION_HPP
#define OMNI_CORE_PURE_EXPRESSION_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/expression.hpp>

namespace omni {
namespace core {
namespace model {

    /**
    An pure_expression is an expression that does not modify it's operands and does not have side-effects.
    A pure_expression does not have any special functionality or properties, it is just a kind of a class of expressions.
    @see modifying_expression
    **/
    class OMNI_CORE_API pure_expression : public expression {
    public:
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
