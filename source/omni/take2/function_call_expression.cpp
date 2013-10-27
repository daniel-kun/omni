#include <omni/take2/function_call_expression.hpp>
#include <omni/take2/function.hpp>

#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>

/**
Initializes this function call expression without any function to call.
**/
omni::take2::function_call_expression::function_call_expression () :
    _function ()
{
}

/**
Initializes this function call expression to call the function `func'.
**/
omni::take2::function_call_expression::function_call_expression (std::shared_ptr <function> func) :
    _function (func)
{
}

/**
Sets the function that this expression should call to `func'.
**/
void omni::take2::function_call_expression::setFunction (std::shared_ptr <function> func)
{
    _function = func;
}

/**
Returns the function that this expression should call. Can be null if no function has been set.
**/
const std::shared_ptr <omni::take2::function> omni::take2::function_call_expression::getFunction () const
{
    return _function;
}

/**
Returns the function that this expression should call. Can be null if no function has been set.
**/
std::shared_ptr <omni::take2::function> omni::take2::function_call_expression::getFunction ()
{
    return _function;
}

llvm::Value * omni::take2::function_call_expression::llvmValue (llvm::BasicBlock * llvmBasicBlock)
{
    llvm::IRBuilder <> builder (llvmBasicBlock);
    return builder.CreateCall (_function->llvmFunction (* llvmBasicBlock->getParent ()->getParent ()), llvm::ArrayRef <llvm::Value*> ());
}
