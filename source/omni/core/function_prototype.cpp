#include <omni/core/function_prototype.hpp>
#include <omni/core/type.hpp>
#include <omni/core/module.hpp>
#include <omni/core/parameter.hpp>

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
omni::core::function_prototype::function_prototype (module & module,
                                                    std::string const & name,
                                                    std::shared_ptr <type> returnType,
                                                    std::vector <std::shared_ptr <omni::core::parameter>> parameters) :
    context_part (name),
    _module (module),
    _llvmFunction (nullptr),
    _returnType (returnType),
    _parameters (parameters)
{
}

omni::core::function_prototype::~function_prototype ()
{
}


/**
Returns the module that this function is defined in.
**/
omni::core::module & omni::core::function_prototype::getModule ()
{
    return _module;
}

/**
Returns the module that this function is defined in.
**/
const omni::core::module & omni::core::function_prototype::getModule () const
{
    return _module;
}

/**
Returns the type that this function returns when it is called at runtime.
**/
const std::shared_ptr <omni::core::type> omni::core::function_prototype::getReturnType () const
{
    return _returnType;
}

/**
Returns the type that this function returns when it is called at runtime.
**/
std::shared_ptr <omni::core::type> omni::core::function_prototype::getReturnType ()
{
    return _returnType;
}

/**
Adds a parameter at the end of the list of parameters that this function should take.
@param parameters The parameter that should be added to the list of parameters for this function.
**/
void omni::core::function_prototype::addParameter (std::shared_ptr <omni::core::parameter> parameter)
{
    _parameters.push_back (parameter);
}

/**
Sets the list of parameters that this function takes to the given parameters;
@param parameters The list of parameters that this function should take.
**/
void omni::core::function_prototype::setParameters (std::vector <std::shared_ptr <omni::core::parameter>> parameters)
{
    _parameters = parameters;
}

/**
@return Returns the list of parameters that this function takes.
**/
std::vector <std::shared_ptr <omni::core::parameter>> omni::core::function_prototype::getParameters () const
{
    return _parameters;
}

/**
Returns a FunctionType for a function with this function_prototype.
**/
llvm::FunctionType * omni::core::function_prototype::llvmFunctionType ()
{
    std::vector <llvm::Type *> params;
    for (auto p : _parameters) {
        params.push_back (p->getType ()->llvmType ());
    }
    return llvm::FunctionType::get (getReturnType ()->llvmType (), params, false);
}
