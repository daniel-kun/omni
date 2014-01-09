#include <omni/core/bitcast_expression.hpp>
#include <omni/core/type.hpp>

#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/NoFolder.h>

/**
Initializes this bitcast_expression to convert the result of sourceExpression to the targetType. sourceExpression->getType ()'s bidwidth
must be of the same bit-width as targetType.
**/
omni::core::bitcast_expression::bitcast_expression (std::shared_ptr <expression> sourceExpression, std::shared_ptr <type> targetType) :
    _sourceExpression (sourceExpression),
    _targetType (targetType)
{

}

std::shared_ptr <omni::core::type> omni::core::bitcast_expression::getType () const
{
    return _targetType;
}

llvm::Value * omni::core::bitcast_expression::llvmValue (llvm::BasicBlock * llvmBasicBlock)
{
    llvm::IRBuilder <true, llvm::NoFolder> builder (llvmBasicBlock);
    return builder.CreateBitCast (_sourceExpression->llvmValue (llvmBasicBlock), _targetType->llvmType ());
}
