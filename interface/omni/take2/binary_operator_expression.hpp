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

    class OMNI_TAKE2_API binary_operator_expression : public expression {
    public:
        enum class binary_operation {
            binary_plus_operation, // +
            binary_minus_operator // -
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
