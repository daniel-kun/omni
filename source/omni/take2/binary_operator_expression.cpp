#include <omni/take2/binary_operator_expression.hpp>
#include <omni/take2/not_implemented_error.hpp>

#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/NoFolder.h>

omni::take2::binary_operator_expression::binary_operator_expression(binary_operation op, std::shared_ptr <expression> leftOperand, std::shared_ptr <expression> rightOperand) :
    _operator (op),
    _leftOperand (leftOperand),
    _rightOperand (rightOperand)
{
}

llvm::Value * omni::take2::binary_operator_expression::llvmValue (llvm::BasicBlock * llvmBasicBlock)
{
    llvm::IRBuilder <true, llvm::NoFolder> builder (llvmBasicBlock);
    switch (_operator) {
    case binary_operation::binary_plus_operation:
        return builder.CreateBinOp (llvm::Instruction::BinaryOps::Add, _leftOperand->llvmValue (llvmBasicBlock), _rightOperand->llvmValue (llvmBasicBlock));
    case binary_operation::binary_minus_operation:
        return builder.CreateBinOp (llvm::Instruction::BinaryOps::Sub, _leftOperand->llvmValue (llvmBasicBlock), _rightOperand->llvmValue (llvmBasicBlock));
    default:
        throw not_implemented_error (__FILE__, __FUNCTION__, __LINE__);
    }
}

