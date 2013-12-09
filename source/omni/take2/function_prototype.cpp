#include <omni/take2/function_prototype.hpp>
#include <omni/take2/type.hpp>
#include <omni/take2/parameter.hpp>

#include <llvm/IR/Type.h>
#include <llvm/IR/Function.h>

/**
Initialises this function prototype with the given function name and return type. You can not call a function by it's function prototype.
To call a function, you either need an object of type `function', or an `external_function', depending on whether the function is defined
in the same module or externally.
@param name The name of the function for this prototype.
@param returnType The return type of the function for this prototype.
@param parameters An optional list of parameters that the function for this prototype receives.
**/
omni::take2::function_prototype::function_prototype (std::string const & name,
                                                     std::shared_ptr <type> returnType,
                                                     std::vector <std::shared_ptr <omni::take2::parameter>> parameters) :
    context_part (name),
    _llvmFunction (nullptr),
    _returnType (returnType),
    _parameters (parameters)
{
}

omni::take2::function_prototype::~function_prototype ()
{
}

/**
Returns the type that this function returns when it is called at runtime.
**/
const std::shared_ptr <omni::take2::type> omni::take2::function_prototype::getReturnType () const
{
    return _returnType;
}

/**
Returns the type that this function returns when it is called at runtime.
**/
std::shared_ptr <omni::take2::type> omni::take2::function_prototype::getReturnType ()
{
    return _returnType;
}

/**
Adds a parameter at the end of the list of parameters that this function should take.
@param parameters The parameter that should be added to the list of parameters for this function.
**/
void omni::take2::function_prototype::addParameter (std::shared_ptr <omni::take2::parameter> parameter)
{
    _parameters.push_back (parameter);
}

/**
Sets the list of parameters that this function takes to the given parameters;
@param parameters The list of parameters that this function should take.
**/
void omni::take2::function_prototype::setParameters (std::vector <std::shared_ptr <omni::take2::parameter>> parameters)
{
    _parameters = parameters;
}

/**
@return Returns the list of parameters that this function takes.
**/
std::vector <std::shared_ptr <omni::take2::parameter>> omni::take2::function_prototype::getParameters () const
{
    return _parameters;
}

/**
Returns a FunctionType for a function with this function_prototype.
**/
llvm::FunctionType * omni::take2::function_prototype::llvmFunctionType ()
{
    std::vector <llvm::Type *> params;
    for (auto p : _parameters) {
        params.push_back (p->getType ()->llvmType ());
    }
    return llvm::FunctionType::get (getReturnType ()->llvmType (), params, false);
}
