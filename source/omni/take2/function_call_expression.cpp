#include <omni/take2/function_call_expression.hpp>
#include <omni/take2/function.hpp>

#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>

/**
Initializes this function call expression without any function to call.
**/
omni::take2::function_call_expression::function_call_expression () :
    _function (),
    _parameters ()
{
}

/**
Initializes this function call expression to call the function `func'.
**/
omni::take2::function_call_expression::function_call_expression (std::shared_ptr <function> func) :
    _function (func),
    _parameters ()
{
}

omni::take2::function_call_expression::function_call_expression (std::shared_ptr <function> func, std::vector <std::shared_ptr <expression>> parameters) :
    _function  (func),
    _parameters (parameters)
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

/**
Adds the parameter to the list of parameters that will be fed to the function-call. Note that the number and types of parameters
must match those of the function that has been passed to the ctor or was set using setFunction().
@param parameter The parameter that will be fed to the function that will be called by this expression.
**/
void omni::take2::function_call_expression::addParameter (std::shared_ptr <expression> parameter)
{
    _parameters.push_back (parameter);
}

/**
Sets a list of parameter that will be fed to the function-call. Note that the number and types of parameters
must match those of the function that has been passed to the ctor or was set using setFunction().
@param parameters The list of parameters that will be fed to thefunction that will be called by this expression.
**/
void omni::take2::function_call_expression::setParameters (std::vector <std::shared_ptr <expression>> parameters)
{
    _parameters = parameters;
}

/**
@return Returns a llvm::CallInst that has been constructed by a call to llvm::IRBuilder<>::CreateCall.
You can safely dynamic_cast the result to a llvm::CallInst.
**/
llvm::Value * omni::take2::function_call_expression::llvmValue (llvm::BasicBlock * llvmBasicBlock)
{
    llvm::IRBuilder <> builder (llvmBasicBlock);
    return builder.CreateCall (_function->llvmFunction (* llvmBasicBlock->getParent ()->getParent ()), llvm::ArrayRef <llvm::Value*> ());
}
