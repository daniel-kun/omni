#include <omni/core/model/entity.hpp>
#include <omni/core/model/scope.hpp>
#include <omni/core/model/module.hpp>
#include <omni/core/context.hpp>

/**
@brief Initializes this entity with an empty name and an invalid id.

The id will be set as soon as this entity is added to a context.
**/
omni::core::model::entity::entity () :
    _parent (),
    _name (),
    _id ()
{
}

/**
@brief Initializes this entity with the given name.

The id will be set as soon as this entity is added to a context.
@param name The name for this entity.
@see getName
**/
omni::core::model::entity::entity (std::string const & name) :
    _parent (),
    _name (name),
    _id ()
{
}

/**
@brief Initializes this entity within the given parent and with the given id and name.

@see getName
@see getId
**/
omni::core::model::entity::entity (omni::core::id entityId, std::string const & name) :
    _parent (),
    _name (name),
    _id (entityId)
{
}

omni::core::model::entity::~entity ()
{
    clearComponents ();
}

/**
@brief Sets a new id for this entity.

This function should usually never be called directly. A new id is automatically assigned as soon as this entity becomes part of a module (see getModule()).

Relations throughout this context are not affected by changing an id.
However, changing the id will affect external resources that are relating to this entity.
For example, if another Omni project is calling a function from this context, the call can no longer be resolved when the function's id is changed.
For all public entities, the id should never be changed in it's whole lifetime.

The id's main purpose is to maintain relations while serializing or deserializing the model.
@param newId The new id that will be assigned to this entity.
@see getId
**/
void omni::core::model::entity::setId (omni::core::id newId)
{
    _id = newId;
}

/**
@brief Returns the unique id of this entity.

@return The current id of this entity.
@see setId
**/
omni::core::id omni::core::model::entity::getId () const
{
    return _id;
}

/**
@brief Abstract. Returns the domain of this entity.

The domain is fixed for every class and does not change.

<b>Important:</b> This function needs to be reimplemented by every class directly or indirectly deriving from entity that is not abstract.
@return The domain of this entity.
**/
omni::core::domain omni::core::model::entity::getDomain () const
{
    return domain::invalid;
}

/**
@brief Changes the name of this entity.
@see getName
**/
void omni::core::model::entity::setName (const std::string & name)
{
    _name = name;
}

/**
@brief Returns the name of this entity.

The name does not need to be unique in a given scope - however, it should be, to be able to distinguish two different entities with the same name.
@return The current name of this entity.
@see setName
@see getId
**/
std::string omni::core::model::entity::getName () const
{
    return _name;
}

/**
@brief Changes the parent of this entity to the given parent.

When this entity does not have an id, yet, and the new parent is already added to a module, this entity and all components 
that do not already have an id will be assigned a newly created id each.

setParent() should never be called explicitly - the parent is automatically changed as soon as this entity
becomes a component of another entity.
@see getParent
**/
void omni::core::model::entity::setParent (entity * parent)
{
    _parent = parent;
    module * mod = getModule ();
    if (mod != nullptr) {
        updateIds ();
    }
}

/**
@brief Returns the parent of this entity.

If this entity is part of a scope, that scope is returned. If this entity was not added to another entity, yet, nullptr is returned.

The return value of getParent can change when setParent is called. This usually happens when this entity is added as a component of another entity.

The returned parent can be modified.
@return The current parent of this entity. Can be nullptr.
@see setParent
**/
omni::core::model::entity * omni::core::model::entity::getParent ()
{
    return _parent;
}

/**
@brief Returns the parent of this entity.

If this entity is part of a scope, that scope is returned. If this entity was not added to another entity, yet, nullptr is returned.

The return value of getParent can change when setParent is called. This usually happens when this entity is added as a component of another entity.

The returned parent is const and can not be modified.
@return The current parent of this entity. Can be nullptr.
@see setParent
**/
const omni::core::model::entity * omni::core::model::entity::getParent () const
{
    return _parent;
}

/**
@brief Returns the module that this entity resides in.

This entiy's module is equivalent the parent's module. If this entity is not part of a parent-hierarchy that in turn has been added to
a module, this entity itself is not part of a module and nullptr is returned.

The return value of getModule can change when setParent is called. This usually happens when this entity is added as a component of another entity.

The returned module can be modified.
@return The module that this entity resides in. Can be nullptr.
**/
omni::core::model::module * omni::core::model::entity::getModule ()
{
    if (getParent () != nullptr) {
        return getParent ()->getModule ();
    } else {
        return nullptr;
    }
}

/**
@brief Returns the module that this entity resides in.

This entiy's module is equivalent the parent's module. If this entity is not part of a parent-hierarchy that in turn has been added to
a module, this entity itself is not part of a module and nullptr is returned.

The return value of getModule can change when setParent is called. This usually happens when this entity is added as a component of another entity.

The returned module is const and can not be modified.
@return The module that this entity resides in. Can be nullptr.
**/
const omni::core::model::module * omni::core::model::entity::getModule () const
{
    if (getParent () != nullptr) {
        return getParent ()->getModule ();
    } else {
        return nullptr;
    }
}

/**
@brief Returns the context that this entity resides in.

This entiy's context is equivalent the module's context. If this entity is not part of a module, it is not part of a context, either.

The return value of getContext can change when setParent is called. This usually happens when this entity is added as a component of another entity.

The returned context can be modified.
@return The context that this entity resides in. Can be nullptr.
**/
omni::core::context * omni::core::model::entity::getContext ()
{
    module * mod = getModule ();
    if (mod != nullptr) {
        return mod->getContext ();
    } else {
        return nullptr;
    }
}

/**
@brief Returns the context that this entity resides in.

This entiy's context is equivalent the module's context. If this entity is not part of a module, it is not part of a context, either.

The return value of getContext can change when setParent is called. This usually happens when this entity is added as a component of another entity.

The returned context can be modified.
@return The context that this entity resides in. Can be nullptr.
**/
const omni::core::context * omni::core::model::entity::getContext () const
{
    module const * mod = getModule ();
    if (mod != nullptr) {
        return mod->getContext ();
    } else {
        return nullptr;
    }
}

/**
@brief Adds or overwrites a component for the given domain and the given name.

For an explanation of what a component is, @see getComponents()

Adds `entity' as a component for the given domain and with the given name. When adding an entity as a component, that entity's parent is set to this entity.
If such a component already exists, it is overwritten and it's parent is set to nullptr.

If entity is nullptr, instead of adding a new component, the given component is removed, if it exists.
In other termns, calling setComponent (someDomain, someName, nullptr) has the same meaning as removeComponent (someDomain, someName).

Note that a component's name has nothing to do with an entity's name that can be retrieved by getName().
@param domain The domain that the component should be stored in.
@param name The name that the component should be stored as.
@param entity The entity that should be stored as a component of this entity.
**/
void omni::core::model::entity::setComponent (omni::core::domain domain, std::string name, std::shared_ptr <entity> entity)
{
    if (! entity) {
        removeComponent (domain, name);
    } else {
        auto it = _components [domain].find (name);
        // If a component with this name exists, the new entity will overwrite it. Hence the old entity is not a component of this entity anymore,
        // which in turn means that this entity is not it's parent anymore:
        if (it != _components [domain].end ()) {
            it->second->setParent (nullptr);
        }
        _components [domain] [name] = entity;
        entity->setParent (this);
    }
}

/**
@brief Returns a list of all components of this entity.

A component is a part of an entity, and all components together are used to build up an entity.

There are some entities that have components and others that don't. For example, the variable_expression does not have a component, while the variable_declaration_expression
has the initialization expression as a component. While variable_expression *references* a variable_declaration_expression, the variable_declaration_expression is not part of
the variable_expression and therefore is not a component of it.

This entity is the parent of all of it's components. It's a direct parent-child-relationship.

The returned list of components is const, so that the list and the contained components can not be modified.
@return A list of all components of this entity.
**/
const omni::core::model::entity::domain_to_name_to_entities_map & omni::core::model::entity::getComponents () const
{
    return _components;
}

/**
@brief Returns a list of all components of this entity.

A component is a part of an entity, and all components together are used to build up an entity.

There are some entities that have components and others that don't. For example, the variable_expression does not have a component, while the variable_declaration_expression
has the initialization expression as a component. While variable_expression *references* a variable_declaration_expression, the variable_declaration_expression is not part of
the variable_expression and therefore is not a component of it.

This entity is the parent of all of it's components. It's a direct parent-child-relationship.

The returned list of components is a copy of the component list, so that the component list of this entity can not be modified, but the contained components can be modified.
@return A list of all components of this entity.
**/
omni::core::model::entity::domain_to_name_to_entities_map omni::core::model::entity::getComponents ()
{
    return _components;
}

/**
@brief Returns a list of components for the given domain.

For an explanation of what a component is, @see getComponents()

Which domains are used to store the components depends on the actual entity, see the respective documentation of the actual entity's class.

The returned list is const, so that the list and the contained components can not be modified.
@param domain The domain that the components are stored in.
@return A list of components for the given domain.
@see getDomain()
**/
const omni::core::model::entity::name_to_entities_map omni::core::model::entity::getComponents (omni::core::domain domain) const
{
    auto it = _components.find (domain);
    if (it != _components.end ()) {
        return it->second;
    } else {
        return omni::core::model::entity::name_to_entities_map ();
    }
}

/**
@brief Returns a list of components for the given domain.

For an explanation of what a component is, @see getComponents()

Which domains are used to store the components depends on the actual entity, see the respective documentation of the actual entity's class.

The returned list is a copy and can be modified, and the contained components can be modified, too.
@param domain The domain that the components are stored in.
@return A list of components for the given domain.
@see getDomain()
**/
omni::core::model::entity::name_to_entities_map omni::core::model::entity::getComponents (omni::core::domain domain)
{
    return _components [domain];
}

/**
@brief Returns the component that is stored for the given domain with the given name.

For an explanation of what a component is, @see getComponents()

Which domains and names are used to store the components depends on the actual entity, see the respective documentation of the actual entity's class.

Note that a component's name has nothing to do with an entity's name that can be retrieved by getName().
@param domain The domain that the component is stored in.
@param name The name that the component is stored as.
@return The component that is stored for the given domain with the given name. Returns nullptr if the component does not exist.
**/
std::shared_ptr <omni::core::model::entity> omni::core::model::entity::getComponent (omni::core::domain domain, std::string name) const
{
    auto c = _components.find (domain);
    if (c != _components.end ()) {
        auto it = c->second.find (name);
        if (it != c->second.end ()) {
            return it->second;
        }
    }
    return std::shared_ptr <entity> ();
}

/**
@brief Returns a list of components for the given domain whose names start with the given prefix.

For an explanation of what a component is, @see getComponents()

This function can be used when an entity contains a list of components with the same meaning, such as a function contains a list of parameters.
All parameters start with the same name, so a list of parameters can be retrieved by calling getComponentsStartingWith(omni::core::domain::parameter, "parameter").

@param domain The domain that the components are stored in.
@param prefix The prefix that the names of the components start with.
@return A list that maps the component's name to the stored entity.
**/
std::map <std::string, std::shared_ptr <omni::core::model::entity>> omni::core::model::entity::getComponentsStartingWith (omni::core::domain domain, std::string prefix) const
{
    std::map <std::string, std::shared_ptr <omni::core::model::entity>> result;
    auto c = _components.find (domain);
    if (c != _components.end ()) {
        for (auto i : c->second) {
            if (i.first.find (prefix) == 0) {
                result [i.first] = i.second;
            }
        }
    }
    return result;
}

/**
@brief Returns the entity with the given id, if it was found in this entity's list of components, or nullptr, if not.

The entity is looked up in each domain, since entities can be stored in component-lists for domains that do not match the entity's domain.

@param id The id of the entity that should be returned. This should not be an invalid id.
@return The entity with the id, if such has been added to the context. A null-shared_ptr is returned, if no such entity exists in this scope.
**/
std::shared_ptr <omni::core::model::entity> omni::core::model::entity::lookupComponentById (omni::core::id id)
{
    for (auto c : _components) {
        name_to_entities_map & m = c.second;
        auto found = std::find_if (m.begin (), m.end (), [id] (std::pair <std::string, std::shared_ptr <entity>> f) -> bool {
            return f.second->getId () == id;
        });
        if (found != m.end ()) {
            return found->second;
        }
    }
    return std::shared_ptr <entity> ();
}

/**
@brief Removes the given component.

For an explanation of what a component is, @see getComponents()

Removes an entity from the list of components of the given domain, if it exists.
If the entity does not exist, this call has no effect and returns false.

Note that removing components can make an entity being invalid, because one or more components might be mandatory.

@param domain The domain that the entity that should be removed is stored in.
@param component The entity that should be removed from the list of components for the given domain.
@return Returns true if such a component existed and was removed. Returns false if no such component exists.
**/
bool omni::core::model::entity::removeComponent (omni::core::domain domain, std::shared_ptr <entity> component)
{
    auto & domainComponents = _components [domain];
    auto it = std::find_if (
        domainComponents.begin (),
        domainComponents.end (),
        [component] (std::pair <std::string, std::shared_ptr <entity>> item) -> bool {
            return item.second == component;
        });
    if (it != domainComponents.end ()) {
        it->second->setParent (nullptr);
        domainComponents.erase (it);
        return true;
    } else {
        return false;
    }
}

/**
@brief Removes the given component.

For an explanation of what a component is, @see getComponents()

Removes an entity from the list of components of the given domain with the given name.
If the entity does not exist, this call has no effect and returns false.

Note that removing components can make an entity being invalid, because one or more components might be mandatory.

@param domain The domain that the entity that should be removed is stored in.
@param name The full name of the component that should be removed.
@return Returns true if such a component existed and was removed. Returns false if no such component exists.
**/
bool omni::core::model::entity::removeComponent (omni::core::domain domain, std::string name)
{
    auto & domainComponents = _components [domain];
    auto it = domainComponents.find (name);
    if (it != domainComponents.end ()) {
        it->second->setParent (nullptr);
        domainComponents.erase (it);
        return true;
    } else {
        return false;
    }
}

/**
@brief Removes all components stored in the given domain from this entity.

For an explanation of what a component is, @see getComponents()

Clears the list of components for the given domain, so that getComponent(domain) will return an empty list.

Note that removing components can make an entity being invalid, because one or more components might be mandatory.

@param domain All components stored for this domain in this entity will be removed.
**/
void omni::core::model::entity::clearComponents (omni::core::domain domain)
{
    for (auto i : _components [domain]) {
        i.second->setParent (nullptr);
    }
    _components [domain].clear ();
}

/**
@brief Removes all components from this entity.

For an explanation of what a component is, @see getComponents()

Clears the list of components for this entity for all domains.

Note that removing components can make an entity being invalid, because one or more components might be mandatory.
**/
void omni::core::model::entity::clearComponents ()
{
    for (auto i : _components) {
        for (auto j : i.second) {
            j.second->setParent (nullptr);
        }
    }
    _components.clear ();
}

/**
Can be overridden by specific entities.
Overrides can add entries to 'libraries'. These entries will be added to the linker when @see context::emitSharedLibraryFile is used to create
a shared library file.
@param libraries A list of libraries that will be included when linking the module of this entity. If the same library is added by multiple entities,
the library will only be linked once.
**/
void omni::core::model::entity::fillLibraries (std::set <std::string> & libraries)
{
}

/**
Recursively sets the ids of all components their components that do not have an id, yet.
Only call this function when getModule () does not return nullptr!
**/
void omni::core::model::entity::updateIds ()
{
    // Set ids for components that do not already have an id:
    module * mod = getModule ();
    if (! getId ().isValid ()) {
        setId (mod->createId (getDomain ()));
    }
    for (auto d : getComponents ()) {
        for (auto c : d.second) {
            if (! c.second->getId ().isValid ()) {
                c.second->updateIds ();
            }
        }
    }
}
