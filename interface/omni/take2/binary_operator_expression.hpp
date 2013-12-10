#ifndef OMNI_TAKE2_BINARY_OPERATOR_EXPRESSION_HPP
#define OMNI_TAKE2_BINARY_OPERATOR_EXPRESSION_HPP

#include <omni/take2/take2.hpp>
#include <omni/take2/expression.hpp>
#include <memory>

namespace llvm {
    class Value;
    class BasicBlock;
}

namespace omni {
namespace take2 {

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
    class OMNI_TAKE2_API binary_operator_expression : public expression {
    public:
        enum class binary_operation {
            binary_plus_operation, // +
            binary_minus_operation // -
        };

        binary_operator_expression (binary_operation op, std::shared_ptr <expression> leftOperand, std::shared_ptr <expression> rightOperand);

        llvm::Value * llvmValue (llvm::BasicBlock * llvmBasicBlock) override;

        std::shared_ptr <expression> getLeftOperand ();
        std::shared_ptr <expression> getRightOperand ();

    private:
        binary_operation _operator;
        std::shared_ptr <expression> _leftOperand;
        std::shared_ptr <expression> _rightOperand;
    };
} // namespace take2
} // namespace omni

#endif // include guard
