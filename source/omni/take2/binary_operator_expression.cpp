#include <omni/take2/binary_operator_expression.hpp>

#include <llvm/IR/IRBuilder.h>

omni::take2::binary_operator_expression::binary_operator_expression(binary_operation op, std::shared_ptr <expression> leftOperand, std::shared_ptr <expression> rightOperand) :
    _operator (op),
    _leftOperand (leftOperand),
    _rightOperand (rightOperand)
{
}

llvm::Value * omni::take2::binary_operator_expression::llvmValue (llvm::BasicBlock * llvmBasicBlock)
{
    llvm::IRBuilder <> builder (llvmBasicBlock);
    return builder.CreateBinOp (llvm::Instruction::BinaryOps::Add, _leftOperand->llvmValue (llvmBasicBlock), _rightOperand->llvmValue (llvmBasicBlock));
}

