#include <omni/core/binary_operator_expression.hpp>
#include <omni/core/context.hpp>
#include <omni/core/not_implemented_error.hpp>
#include <omni/core/type_mismatch_error.hpp>
#include <omni/core/type.hpp>

#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/NoFolder.h>

/**
Initializes this binary_operator_expression with the binary_operation op and the leftOperand and rightOperand.
@param op The operation that is to be performed with leftOperand and rightOperand. E.g. in "5 - 7", this is "-" or binary_operation::binary_minus_operation.
@param leftOperand The left operand of this operation. E.g. in "5 + 7", this is "5".
@param rightOperand The right operand of this operation. E.g. in "5 / 7", this is "7".
**/
omni::core::binary_operator_expression::binary_operator_expression (context & context,
                                                                    binary_operation op,
                                                                    std::shared_ptr <expression> leftOperand,
                                                                    std::shared_ptr <expression> rightOperand) :
    _type (),
    _operator (op),
    _leftOperand (leftOperand),
    _rightOperand (rightOperand)
{
    if (_leftOperand->getType () != _rightOperand->getType ()) {
        throw type_mismatch_error (* leftOperand->getType (), * rightOperand->getType ());
    }
    switch (_operator) {
    case binary_operation::binary_lessthan_operation:
        _type = context.sharedBasicType (type_class::t_boolean);
        break;
    case binary_operation::binary_minus_operation:
    case binary_operation::binary_plus_operation:
        _type = _leftOperand->getType ();
        break;
    default:
        throw not_implemented_error (__FILE__, __FUNCTION__, __LINE__);
    }
}

/**
Returns the type of this binary_operator_expression. The type is deduced from the left and right operands.
**/
std::shared_ptr <omni::core::type> omni::core::binary_operator_expression::getType () const 
{
    return _type;
}

/**
@internal
**/
llvm::Value * omni::core::binary_operator_expression::llvmValue (llvm::BasicBlock * llvmBasicBlock)
{
    llvm::IRBuilder <true, llvm::NoFolder> builder (llvmBasicBlock);
    llvm::Value * lhs = _leftOperand->llvmValue (llvmBasicBlock);
    llvm::Value * rhs = _rightOperand->llvmValue (llvmBasicBlock);
    switch (_operator) {
    case binary_operation::binary_lessthan_operation:
        switch (_leftOperand->getType ()->getTypeClass ()) {
        case type_class::t_signedInt:
            return builder.CreateICmp (llvm::CmpInst::ICMP_SLT, lhs, rhs);
        default:
            throw not_implemented_error (__FILE__, __FUNCTION__, __LINE__);
        }
    case binary_operation::binary_plus_operation:
        return builder.CreateBinOp (llvm::Instruction::BinaryOps::Add, lhs, rhs);
    case binary_operation::binary_minus_operation:
        return builder.CreateBinOp (llvm::Instruction::BinaryOps::Sub, lhs, rhs);
    default:
        throw not_implemented_error (__FILE__, __FUNCTION__, __LINE__);
    }
}

