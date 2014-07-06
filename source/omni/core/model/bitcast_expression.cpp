#include <omni/core/model/bitcast_expression.hpp>
#include <omni/core/model/type.hpp>

#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/NoFolder.h>

/**
Initializes this bitcast_expression to convert the result of sourceExpression to the targetType. sourceExpression->getType ()'s bidwidth
must be of the same bit-width as targetType.
**/
omni::core::model::bitcast_expression::bitcast_expression (std::shared_ptr <expression> sourceExpression, std::shared_ptr <type> targetType) :
    cast_expression (),
    _targetType (targetType)
{
    setSourceExpression (sourceExpression);
}

omni::core::domain omni::core::model::bitcast_expression::getDomain () const
{
    return domain::bitcast_expression;
}

void omni::core::model::bitcast_expression::setSourceExpression (std::shared_ptr <omni::core::model::expression> sourceExpression)
{
    setComponent (domain::expression, "sourceExpression", sourceExpression);
}

std::shared_ptr <omni::core::model::expression> omni::core::model::bitcast_expression::getSourceExpression () const
{
    return getComponentAs <expression> (domain::expression, "sourceExpression");
}


std::shared_ptr <omni::core::model::type> omni::core::model::bitcast_expression::getType () const
{
    return _targetType;
}

omni::core::statement_emit_result omni::core::model::bitcast_expression::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    llvm::IRBuilder <true, llvm::NoFolder> builder (llvmBasicBlock);
    return statement_emit_result (llvmBasicBlock, builder.CreateBitCast (getSourceExpression ()->llvmEmit (llvmBasicBlock).getValue (), _targetType->llvmType ()));
}
