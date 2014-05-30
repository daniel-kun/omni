#ifndef OMNI_CORE_EXPRESSION_HPP
#define OMNI_CORE_EXPRESSION_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/statement.hpp>

#include <memory>

namespace llvm {
    class BasicBlock;
    class Value;
}

namespace omni {
namespace core {
namespace model {
    class type;

    /**
    An expression is a statement that returns or is a value. An expression can stand alone as a statement, or it can be part of other statements or expressions.
    For example, the binary_operator_expression has one expression as the left hand side operand and
    another expression as the right hand side operand. A function_call_expression receives expressions as it's parameters and is itself an expression.
    **/
    class OMNI_CORE_API expression : public statement {
    public:
        expression ();

        virtual std::shared_ptr <type> getType () const = 0;
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
