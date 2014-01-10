#ifndef OMNI_CORE_BINARY_OPERATOR_EXPRESSION_HPP
#define OMNI_CORE_BINARY_OPERATOR_EXPRESSION_HPP

#include <omni/core/core.hpp>
#include <omni/core/pure_expression.hpp>

#include <memory>

namespace llvm {
    class Value;
    class BasicBlock;
}

namespace omni {
namespace core {
    class type;

    /**
    A binary_operator_expression is an expression that returns the result of a binary operator that is applied to it's two operands.
    A binary operator is an operator that takes a left-hand-side and a right-hand-side operand.
    Examples are:
    1 + 5
    5 - 1
    9 * 2
    8 / 4
    5 mod 2
    5 div 2
    5 bit-and 2
    3 bit-or 5
    9 bit-xor 2
    **/
    class OMNI_CORE_API binary_operator_expression : public pure_expression {
    public:
        enum class binary_operation {
            binary_lessthan_operation,
            binary_plus_operation, // +
            binary_minus_operation // -
        };

        binary_operator_expression (context & context, binary_operation op, std::shared_ptr <expression> leftOperand, std::shared_ptr <expression> rightOperand);

        std::shared_ptr <type> getType () const override;

        statement_emit_result llvmEmit (llvm::BasicBlock * llvmBasicBlock) override;

        std::shared_ptr <expression> getLeftOperand ();
        std::shared_ptr <expression> getRightOperand ();

    private:
        std::shared_ptr <type> _type;
        binary_operation _operator;
        std::shared_ptr <expression> _leftOperand;
        std::shared_ptr <expression> _rightOperand;
    };
} // namespace core
} // namespace omni

#endif // include guard
