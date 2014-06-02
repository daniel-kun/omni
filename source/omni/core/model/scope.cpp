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
Initializes this scope in the parent scope `scope' with the name `name'. A new, random id will be assigned to this scope.
**/
omni::core::model::scope::scope (std::string name) :
    entity (name)
{
}

/**
Initializes this existing scope in the given parent scope with the given name and scopeId.
**/
omni::core::model::scope::scope (id scopeId, std::string name) :
    entity (scopeId, name)
{
}

omni::core::model::scope::~scope ()
{
}

/**
Finds any entity of this scope by it's unique id. The entity has to be added to this context before it can be found.
This happens when the entity is created using one of the create...-functions or the entity has been added via one of the add...-functions.
@param id The id of the entity that should be returned. This should not be an invalid id.
@return The entity with the id, if such has been added to the context. A null-shared_ptr is returned, if no such entity exists in this scope.
**/
std::shared_ptr <omni::core::model::entity> omni::core::model::scope::findContentById (omni::core::id id)
{
    name_to_entities_map & m (getComponents (id.getDomain ()));
    auto found = std::find_if (m.begin (), m.end (), [id] (std::pair <std::string, std::shared_ptr <entity>> f) -> bool {
        return f.second->getId ().getId () == id.getId ();
    });
    if (found != m.end ()) {
        return found->second;
    } else {
        return std::shared_ptr <entity> ();
    }
}

/**
Creates a new function object for the function with the name `name', adds it to this scope and returns it.
Calling createFunction is the same as creating a new function with this scope as the first paramter and then calling addFunction().
That's why this function will automatically be assigned a new id.
@param name The name of the function. There may not be a function with the same name in the context, otherwise an already_exits_error exception will be thrown.
@param returnType The type that the function returns.
@param body The body of the function.
@exception already_exists_error Is thrown when a function with the name `name' already exists in this context.
**/
std::shared_ptr <omni::core::model::function> omni::core::model::scope::createFunction (std::string const & name, std::shared_ptr <type> returnType, std::shared_ptr <block> body)
{
    std::shared_ptr <function> result (new function (name, returnType, body));
    addFunction (result);
    return result;
}

/**
Adds the function `function' to this scope, if there is not already another function with the same name.
`function' will automatically be assigned a new id before it is added to this scope.
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
Returns the function with the name `name', if such a function exists in this scope.
Only functions that were created using createFunction or were added via addFunction are part of this scope.
@param The name of the function that should be returned. Should not be empty.
@return The function with the name `name' that has previously been added to this context.
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
Removes the function `function' from this scope. This only has an effect if `function' was previously added to this scope by creating it using
createFunction or adding it via addFunction.
@param function The function to be removed from this scope.
@return true, if `function' was part of this scope and has been removed. false, if `function' was not found.
**/
bool omni::core::model::scope::removeFunction (std::shared_ptr <model::function_prototype> function)
{
    return removeComponent (domain::function, function);
}

void omni::core::model::scope::setComponent (omni::core::domain domain, std::string name, std::shared_ptr <omni::core::model::entity> entity)
{
    omni::core::model::entity::setComponent (domain, name, entity);
    if (entity) {
        entity->setParent (this);
    }
}

