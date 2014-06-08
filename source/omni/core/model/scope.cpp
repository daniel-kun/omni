#include <omni/core/model/scope.hpp>
#include <omni/core/context.hpp>
#include <omni/core/model/module.hpp>
#include <omni/core/model/function.hpp>
#include <omni/core/model/block.hpp>
#include <omni/core/logic_error.hpp>
#include <omni/core/already_exists_error.hpp>
#include <omni/core/verification_failed_error.hpp>

#include <boost/format.hpp>

#include <sstream>

/**
@brief Initializes this scope with an empty name and an invalid id.

The id will be set as soon as this entity is added to a context.
**/
omni::core::model::scope::scope () :
    entity ()
{
}

/**
@brief Initializes this scope with the given name and an invalid id.

The id will be set as soon as this entity is added to a context.
@see getName
**/
omni::core::model::scope::scope (std::string name) :
    entity (name)
{
}

/**
@brief Initializes this entity within the given parent and with the given id and name.
@see getName
@see getId
**/
omni::core::model::scope::scope (id scopeId, std::string name) :
    entity (scopeId, name)
{
}

omni::core::model::scope::~scope ()
{
}

/**
@brief Creates a new function with the given characteristics, adds it to this scope and returns it.

The function's parent will be set to this scope and the body's and paremeter's parent will be set to the created function.

Calling createFunction is the same as creating a new omni::core::model::function and then calling addFunction().
@param name The name of the function. There may not be a function with the same name in this scope, otherwise an already_exits_error exception will be thrown.
@param returnType The type of the value that the function returns.
@param body The body of the function.
@param parameters An optional list of parameters that the function receives.
@param isExported Specifies, whether this function is visible from outside the module it is defined in. @see function::isExported().
@exception already_exists_error Is thrown when a function with the given name already exists in this scope.
**/
std::shared_ptr <omni::core::model::function> omni::core::model::scope::createFunction (
    std::string const & name,
    std::shared_ptr <type> returnType,
    std::shared_ptr <block> body,
    std::vector <std::shared_ptr <parameter>> parameters,
    bool isExported)
{
    std::shared_ptr <function> result (new function (name, returnType, body, parameters, isExported));
    addFunction (result);
    return result;
}

/**
Adds the given function to this scope, if there is not already another function with the same name.

The function's parent will be set to this scope.

@param function The function that should be added to this scope.
@exception already_exists_error Is thrown when a function with the same name as `function's name already exists in this scope.
**/
void omni::core::model::scope::addFunction (std::shared_ptr <function_prototype> function)
{
    std::shared_ptr <function_prototype> func = findFunctionByName (function->getName ());
    if (func.get () != nullptr) {
        throw already_exists_error (domain::function, function->getName ());
    }
    setComponent (domain::function, function->getName (), function);
}

/**
@brief Returns the function with the given name, if such a function exists in this scope.

Only functions that were created using createFunction or were added via addFunction are part of this scope.
@param name The name of the function that should be returned. Should not be empty.
@return The function with the given name that has previously been added to this context.
**/
std::shared_ptr <omni::core::model::function_prototype> omni::core::model::scope::findFunctionByName (std::string const & name)
{
    name_to_entities_map & functionMap (getComponents (domain::function));
    auto found = std::find_if (functionMap.begin (), functionMap.end (), [name] (std::pair <std::string, std::shared_ptr <entity>> f) -> bool {
        return f.second->getName () == name;
    });
    if (found != functionMap.end ()) {
        return std::dynamic_pointer_cast <function_prototype> (found->second);
    } else {
        return std::shared_ptr <function_prototype> ();
    }
}

/**
@brief Removes the given from this scope.

This only has an effect if `function' was previously added to this scope by creating it using createFunction or adding it via addFunction.
@param function The function to be removed from this scope.
@return true, if `function' was part of this scope and has been removed. false, if `function' was not found.
**/
bool omni::core::model::scope::removeFunction (std::shared_ptr <model::function_prototype> function)
{
    return removeComponent (domain::function, function);
}
