#ifndef OMNI_CORE_EXPRESSION_HPP
#define OMNI_CORE_EXPRESSION_HPP

#include <omni/core/core.hpp>

namespace llvm {
    class BasicBlock;
    class Value;
}

namespace omni {
namespace core {

    /**
    An expression is something that returns or is a value. An expression can be a statement, when it's wrapped in an expression_statement
    or it can be part of other statements. For example, the binary_operator_expression has one expression as the left hand side operand and
    another expression as the right hand side operand. A function_call_expression receives expressions as it's parameters and is itself an expression.
    **/
    class OMNI_CORE_API expression {
    public:
        virtual ~ expression () = 0;

        virtual llvm::Value * llvmValue (llvm::BasicBlock * llvmBasicBlock) = 0;
    };

} // namespace core
} // namespace omni

#endif // include guard
