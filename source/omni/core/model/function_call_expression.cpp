#include <omni/core/model/function_call_expression.hpp>
#include <omni/core/model/function_prototype.hpp>

#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/NoFolder.h>

#include <boost/lexical_cast.hpp>

/**
Initializes this function call expression without any function to call.
**/
omni::core::model::function_call_expression::function_call_expression () :
    modifying_expression (),
    _function (),
    _paramCount (0u)
{
}

/**
Initializes this function call expression to call the function `func'.
**/
omni::core::model::function_call_expression::function_call_expression (std::shared_ptr <function_prototype> func) :
    modifying_expression (),
    _function (func),
    _paramCount (0u)
{
}

omni::core::model::function_call_expression::function_call_expression (std::shared_ptr <function_prototype> func, std::vector <std::shared_ptr <expression>> parameters) :
    modifying_expression (),
    _function  (func),
    _paramCount (0u)
{
    setParameters (parameters);
}

omni::core::domain omni::core::model::function_call_expression::getDomain () const
{
    return domain::function_call_expression;
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
void omni::core::model::function_call_expression::appendParameter (std::shared_ptr <expression> parameter)
{
    setComponent (domain::expression, "parameter" + boost::lexical_cast <std::string> (++ _paramCount), parameter);
}

/**
Sets a list of parameter that will be fed to the function-call. Note that the number and types of parameters
must match those of the function that has been passed to the ctor or was set using setFunction().
@param parameters The list of parameters that will be fed to thefunction that will be called by this expression.
**/
void omni::core::model::function_call_expression::setParameters (std::vector <std::shared_ptr <expression>> parameters)
{
    clearComponents ();
    for (auto i : parameters) {
        appendParameter (i);
    }
}

std::vector <std::shared_ptr <omni::core::model::expression>> omni::core::model::function_call_expression::getParameters ()
{
    std::vector <std::shared_ptr <omni::core::model::expression>> result;
    for (auto i : getComponentsStartingWithAs <expression> (domain::expression, "parameter")) {
        result.push_back (i.second);
    }
    return result;
}

/**
@return Returns a llvm::CallInst that has been constructed by a call to llvm::IRBuilder<>::CreateCall.
You can safely dynamic_cast the result to a llvm::CallInst.
**/
omni::core::statement_emit_result omni::core::model::function_call_expression::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    llvm::IRBuilder <true, llvm::NoFolder> builder (llvmBasicBlock);

    std::vector <llvm::Value*> llvmParameterArguments;
    for (auto p : getParameters ()) {
        llvm::Value * val = p->llvmEmit (llvmBasicBlock).getValue ();
        llvmParameterArguments.push_back (val);
    }
    return statement_emit_result (llvmBasicBlock, builder.CreateCall (_function->llvmFunction (), llvmParameterArguments));
}
