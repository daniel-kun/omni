#include <omni/core/model/function_prototype.hpp>
#include <omni/core/model/module.hpp>
#include <omni/core/model/type.hpp>
#include <omni/core/model/parameter.hpp>

#include <llvm/IR/Type.h>
#include <llvm/IR/Function.h>

#include <boost/lexical_cast.hpp>

/**
@brief Initializes this function prototype with the given function name, return-type and parameters.

@param name The name of the function for this prototype.
@param returnType The return type of the function for this prototype.
@param parameters An optional list of parameters that the function for this prototype receives.
**/
omni::core::model::function_prototype::function_prototype (std::string const & name,
                                                           std::shared_ptr <type> returnType,
                                                           std::vector <std::shared_ptr <omni::core::model::parameter>> parameters) :
    scope (name),
    _returnType (returnType),
    _paramCount (0u)
{
    setParameters (parameters);
}

omni::core::model::function_prototype::~function_prototype ()
{
}

/**
@brief Sets the return-type of this function.

Can be nullptr, if the function should have a void return-type (i.e. does not return a value).

It is important to make sure that the body contains return_statements for each control-flow that match the new return-type.

@param returnType The new return-type of this function.
**/
void omni::core::model::function_prototype::setReturnType (std::shared_ptr <type> returnType)
{
    _returnType = returnType;
}

/**
@brief Returns the type of the value that this function returns when it is called at runtime.

Returns nullptr, if this function does not return a value (i.e. is a "void function").

If this function's return-type is non-void, the body must contain a return_statement that returns a value of the same type in each control-flow.

The returned type is const and can not be modified.
**/
const std::shared_ptr <omni::core::model::type> omni::core::model::function_prototype::getReturnType () const
{
    return _returnType;
}

/**
@brief Returns the type of the value that this function returns when it is called at runtime.

Returns nullptr, if this function does not return a value (i.e. is a "void function").

If this function's return-type is non-void, the body must contain a return_statement that returns a value of the same type in each control-flow.

The returned type can be modified.
**/
std::shared_ptr <omni::core::model::type> omni::core::model::function_prototype::getReturnType ()
{
    return _returnType;
}

/**
@brief Adds a parameter at the end of the list of parameters that this function should take.

The parameter's parent will be changed to this funtion_protype.

@param parameter The parameter that should be appended to the list of parameters for this function.
@see function_prototype()
**/
void omni::core::model::function_prototype::appendParameter (std::shared_ptr <parameter> parameter)
{
    setComponent (domain::parameter, "parameter" + boost::lexical_cast <std::string> (++_paramCount), parameter);
}

/**
@brief Sets the list of parameters that this function takes to the given parameters;

All parameters that have been set before will be cleared.

The parameter's parents will be changed to this funtion_protype.

@param parameters The list of parameters that this function should take.
**/
void omni::core::model::function_prototype::setParameters (std::vector <std::shared_ptr <parameter>> parameters)
{
    _paramCount = 0u;
    clearComponents (domain::parameter);
    for (auto i : parameters) {
        appendParameter (i);
    }
}

/**
@brief Returns the list of parameters that this function takes.

The returned list is a copy of the paremeter-list of this function_prototype.
The contained parameters are const and can not be modified.
@return The list of parameters that this function takes.
**/
std::vector <const std::shared_ptr <omni::core::model::parameter>> omni::core::model::function_prototype::getParameters () const
{
    std::vector <const std::shared_ptr <omni::core::model::parameter>> result;
    for (auto i : getComponentsStartingWithAs <parameter> (domain::parameter, "parameter")) {
        result.push_back (i.second);
    }
    return result;
}

/*
Internal.

Returns an llvm::FunctionType with the same characteristics as this function_prototype.
*/
llvm::FunctionType * omni::core::model::function_prototype::llvmFunctionType ()
{
    std::vector <llvm::Type *> params;
    for (auto p : getParameters ()) {
        params.push_back (p->getType ()->llvmType ());
    }
    return llvm::FunctionType::get (getReturnType ()->llvmType (), params, false);
}
