#include <omni/core/binary_operator_expression.hpp>
#include <omni/core/not_implemented_error.hpp>
#include <omni/core/type_mismatch_error.hpp>

#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/NoFolder.h>

/**
Initializes this binary_operator_expression with the binary_operation op and the leftOperand and rightOperand.
@param op The operation that is to be performed with leftOperand and rightOperand. E.g. in "5 - 7", this is "-" or binary_operation::binary_minus_operation.
@param leftOperand The left operand of this operation. E.g. in "5 + 7", this is "5".
@param rightOperand The right operand of this operation. E.g. in "5 / 7", this is "7".
**/
omni::core::binary_operator_expression::binary_operator_expression (binary_operation op, std::shared_ptr <expression> leftOperand, std::shared_ptr <expression> rightOperand) :
    _operator (op),
    _leftOperand (leftOperand),
    _rightOperand (rightOperand)
{
    if (_leftOperand->getType () != _rightOperand->getType ()) {
        throw type_mismatch_error (* leftOperand->getType (), * rightOperand->getType ());
    }
}

/**
Returns the type of this binary_operator_expression. The type is deduced from the left and right operands.
**/
std::shared_ptr <omni::core::type> omni::core::binary_operator_expression::getType () const 
{
    return _leftOperand->getType ();
}

/**
@internal
**/
llvm::Value * omni::core::binary_operator_expression::llvmValue (llvm::BasicBlock * llvmBasicBlock)
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

