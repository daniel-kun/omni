#include <omni/core/model/function_prototype.hpp>
#include <omni/core/model/module.hpp>
#include <omni/core/model/type.hpp>
#include <omni/core/model/parameter.hpp>

#include <llvm/IR/Type.h>
#include <llvm/IR/Function.h>

#include <boost/lexical_cast.hpp>

/**
Initialises this function prototype with the given function name and return type. You can not call a function by it's function prototype.
To call a function, you either need an object of type `function', or an `external_function', depending on whether the function is defined
in the same module or externally.
@param name The name of the function for this prototype.
@param returnType The return type of the function for this prototype.
@param parameters An optional list of parameters that the function for this prototype receives.
**/
omni::core::model::function_prototype::function_prototype (std::string const & name,
                                                           std::shared_ptr <type> returnType,
                                                           std::vector <std::shared_ptr <omni::core::model::parameter>> parameters) :
    scope (name),
    _returnType (returnType),
    _paramCount (0u),
    _llvmFunction (nullptr)
{
    for (auto i : parameters) {
        addParameter (i);
    }
}

omni::core::model::function_prototype::~function_prototype ()
{
}

/**
Returns the type that this function returns when it is called at runtime.
**/
const std::shared_ptr <omni::core::model::type> omni::core::model::function_prototype::getReturnType () const
{
    return _returnType;
}

/**
Returns the type that this function returns when it is called at runtime.
**/
std::shared_ptr <omni::core::model::type> omni::core::model::function_prototype::getReturnType ()
{
    return _returnType;
}

/**
Adds a parameter at the end of the list of parameters that this function should take.
@param parameters The parameter that should be added to the list of parameters for this function.
**/
void omni::core::model::function_prototype::addParameter (std::shared_ptr <omni::core::model::parameter> parameter)
{
    setComponent (domain::parameter, "parameter" + boost::lexical_cast <std::string> (++_paramCount), parameter);
}

/**
Sets the list of parameters that this function takes to the given parameters;
@param parameters The list of parameters that this function should take.
**/
void omni::core::model::function_prototype::setParameters (std::vector <std::shared_ptr <omni::core::model::parameter>> parameters)
{
    _paramCount = 0u;
    for (auto i : parameters) {
        addParameter (i);
    }
}

/**
@return Returns the list of parameters that this function takes.
**/
std::vector <std::shared_ptr <omni::core::model::parameter>> omni::core::model::function_prototype::getParameters () const
{
    std::vector <std::shared_ptr <omni::core::model::parameter>> result;
    for (auto i : getComponentsStartingWithAs <parameter> (domain::parameter, "parameter")) {
        result.push_back (i.second);
    }
    return result;
}

/**
Returns a FunctionType for a function with this function_prototype.
**/
llvm::FunctionType * omni::core::model::function_prototype::llvmFunctionType ()
{
    std::vector <llvm::Type *> params;
    for (auto p : getParameters ()) {
        params.push_back (p->getType ()->llvmType ());
    }
    return llvm::FunctionType::get (getReturnType ()->llvmType (), params, false);
}
