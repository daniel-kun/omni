#include <omni/core/model/binary_operator_expression.hpp>
#include <omni/core/context.hpp>
#include <omni/core/not_implemented_error.hpp>
#include <omni/core/model/type_mismatch_error.hpp>
#include <omni/core/model/type.hpp>

#include <llvm/IR/IRBuilder.h>
//#include <llvm/IR/NoFolder.h>
#include <llvm/IR/NoFolder.h>

/**
Initializes this binary_operator_expression with the binary_operation op and the leftOperand and rightOperand.
@param op The operation that is to be performed with leftOperand and rightOperand. E.g. in "5 - 7", this is "-" or binary_operation::binary_minus_operation.
@param leftOperand The left operand of this operation. E.g. in "5 + 7", this is "5".
@param rightOperand The right operand of this operation. E.g. in "5 / 7", this is "7".
**/
omni::core::model::binary_operator_expression::binary_operator_expression (
    omni::core::context & context,
    binary_operation op,
    std::shared_ptr <expression> leftOperand,
    std::shared_ptr <expression> rightOperand) :
    pure_expression (),
    _type (),
    _operator (op)
{
    setLeftOperand (leftOperand);
    setRightOperand (rightOperand);

    if (leftOperand->getType () != rightOperand->getType ()) {
        throw type_mismatch_error (* leftOperand->getType (), * rightOperand->getType ());
    }
    switch (_operator) {
    case binary_operation::binary_lessthan_operation:
        _type = context.sharedBasicType (type_class::t_boolean);
        break;
    case binary_operation::binary_minus_operation:
    case binary_operation::binary_plus_operation:
        _type = leftOperand->getType ();
        break;
    default:
        throw not_implemented_error (__FILE__, __FUNCTION__, __LINE__);
    }
}

omni::core::domain omni::core::model::binary_operator_expression::getDomain () const
{
    return domain::binary_operator_expression;
}

void omni::core::model::binary_operator_expression::setLeftOperand (std::shared_ptr <omni::core::model::expression> leftOperand)
{
    setComponent (domain::expression, "leftOperand", leftOperand);
}

std::shared_ptr <omni::core::model::expression> omni::core::model::binary_operator_expression::getLeftOperand () const
{
    return getComponentAs <expression> (domain::expression, "leftOperand");
}

void omni::core::model::binary_operator_expression::setRightOperand (std::shared_ptr <omni::core::model::expression> rightOperand)
{
    setComponent (domain::expression, "rightOperand", rightOperand);
}

std::shared_ptr <omni::core::model::expression> omni::core::model::binary_operator_expression::getRightOperand () const
{
    return getComponentAs <expression> (domain::expression, "rightOperand");
}

/**
Returns the type of this binary_operator_expression. The type is deduced from the left and right operands.
**/
std::shared_ptr <omni::core::model::type> omni::core::model::binary_operator_expression::getType () const 
{
    return _type;
}

/**
@internal
**/
omni::core::statement_emit_result omni::core::model::binary_operator_expression::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    llvm::IRBuilder <true, llvm::NoFolder> builder (llvmBasicBlock);
    std::shared_ptr <expression> leftOperand = getLeftOperand ();
    llvm::Value * lhs = leftOperand->llvmEmit (llvmBasicBlock).getValue ();
    llvm::Value * rhs = getRightOperand ()->llvmEmit (llvmBasicBlock).getValue ();
    switch (_operator) {
    case binary_operation::binary_lessthan_operation:
        switch (leftOperand->getType ()->getTypeClass ()) {
        case type_class::t_signedInt:
            return statement_emit_result (llvmBasicBlock, builder.CreateICmp (llvm::CmpInst::ICMP_SLT, lhs, rhs));
        default:
            throw not_implemented_error (__FILE__, __FUNCTION__, __LINE__);
        }
    case binary_operation::binary_plus_operation:
        return statement_emit_result (llvmBasicBlock, builder.CreateBinOp (llvm::Instruction::BinaryOps::Add, lhs, rhs));
    case binary_operation::binary_minus_operation:
        return statement_emit_result (llvmBasicBlock, builder.CreateBinOp (llvm::Instruction::BinaryOps::Sub, lhs, rhs));
    default:
        throw not_implemented_error (__FILE__, __FUNCTION__, __LINE__);
    }
}

