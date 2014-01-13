#include <omni/core/function_call_expression.hpp>
#include <omni/core/function_prototype.hpp>

#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/NoFolder.h>

/**
Initializes this function call expression without any function to call.
**/
omni::core::model::function_call_expression::function_call_expression () :
    _function (),
    _parameters ()
{
}

/**
Initializes this function call expression to call the function `func'.
**/
omni::core::model::function_call_expression::function_call_expression (std::shared_ptr <function_prototype> func) :
    _function (func),
    _parameters ()
{
}

omni::core::model::function_call_expression::function_call_expression (std::shared_ptr <function_prototype> func, std::vector <std::shared_ptr <expression>> parameters) :
    _function  (func),
    _parameters (parameters)
{

}

std::shared_ptr <omni::core::model::type> omni::core::model::function_call_expression::getType () const
{
    return _function->getReturnType ();
}

/**
Sets the function that this expression should call to `func'.
**/
void omni::core::model::function_call_expression::setFunction (std::shared_ptr <function_prototype> func)
{
    _function = func;
}

/**
Returns the function that this expression should call. Can be null if no function has been set.
**/
const std::shared_ptr <omni::core::model::function_prototype> omni::core::model::function_call_expression::getFunction () const
{
    return _function;
}

/**
Returns the function that this expression should call. Can be null if no function has been set.
**/
std::shared_ptr <omni::core::model::function_prototype> omni::core::model::function_call_expression::getFunction ()
{
    return _function;
}

/**
Adds the parameter to the list of parameters that will be fed to the function-call. Note that the number and types of parameters
must match those of the function that has been passed to the ctor or was set using setFunction().
@param parameter The parameter that will be fed to the function that will be called by this expression.
**/
void omni::core::model::function_call_expression::addParameter (std::shared_ptr <expression> parameter)
{
    _parameters.push_back (parameter);
}

/**
Sets a list of parameter that will be fed to the function-call. Note that the number and types of parameters
must match those of the function that has been passed to the ctor or was set using setFunction().
@param parameters The list of parameters that will be fed to thefunction that will be called by this expression.
**/
void omni::core::model::function_call_expression::setParameters (std::vector <std::shared_ptr <expression>> parameters)
{
    _parameters = parameters;
}

/**
@return Returns a llvm::CallInst that has been constructed by a call to llvm::IRBuilder<>::CreateCall.
You can safely dynamic_cast the result to a llvm::CallInst.
**/
omni::core::statement_emit_result omni::core::model::function_call_expression::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    llvm::IRBuilder <true, llvm::NoFolder> builder (llvmBasicBlock);

    std::vector <llvm::Value*> llvmParameters;
    for (auto p : _parameters) {
        llvm::Value * val = p->llvmEmit (llvmBasicBlock).getValue ();
        llvmParameters.push_back (val);
    }
    return statement_emit_result (llvmBasicBlock, builder.CreateCall (_function->llvmFunction (), llvmParameters));
}
