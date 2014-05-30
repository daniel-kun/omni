#include <omni/core/model/entity.hpp>
#include <omni/core/model/scope.hpp>
#include <omni/core/model/module.hpp>
#include <omni/core/context.hpp>

/**
Initializes this entity with an empty name and an invalid id.
The name can be left empty, as long as the actual kind of context part does not require a name.
The id will be set as soon as this context part is added to a context.
**/
omni::core::model::entity::entity () :
    _parent (),
    _name (),
    _id ()
{
}

/**
Initializes this entity within the given parent and with the given name.
**/
omni::core::model::entity::entity (std::string const & name) :
    _parent (),
    _name (name),
    _id ()
{
}

/**
Initializes this entity within the given parent and with the given id and name.
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

omni::core::context * omni::core::model::entity::getContext ()
{
    module * mod = getModule ();
    if (mod != nullptr) {
        return mod->getContext ();
    } else {
        return nullptr;
    }
}

const omni::core::context * omni::core::model::entity::getContext () const
{
    module const * mod = getModule ();
    if (mod != nullptr) {
        return mod->getContext ();
    } else {
        return nullptr;
    }
}

omni::core::model::module * omni::core::model::entity::getModule ()
{
    if (getParent () != nullptr) {
        return getParent ()->getModule ();
    } else {
        return nullptr;
    }
}

const omni::core::model::module * omni::core::model::entity::getModule () const
{
    if (getParent () != nullptr) {
        return getParent ()->getModule ();
    } else {
        return nullptr;
    }
}

omni::core::model::scope * omni::core::model::entity::getParent ()
{
    return _parent;
}

const omni::core::model::scope * omni::core::model::entity::getParent () const
{
    return _parent;
}

void omni::core::model::entity::setParent (scope * parent)
{
    _parent = parent;
}


std::string omni::core::model::entity::getName () const
{
    return _name;
}

void omni::core::model::entity::setName (const std::string & name)
{
    _name = name;
}

void omni::core::model::entity::setId (omni::core::id newId)
{
    _id = newId;
}

omni::core::id omni::core::model::entity::getId () const
{
    return _id;
}

const omni::core::model::entity::domain_id_to_entities_map & omni::core::model::entity::getComponents () const
{
    return _components;
}

omni::core::model::entity::domain_id_to_entities_map omni::core::model::entity::getComponents ()
{
    return _components;
}

const omni::core::model::entity::id_to_entities_map omni::core::model::entity::getComponents (omni::core::domain domain) const
{
    auto it = _components.find (domain);
    if (it != _components.end ()) {
        return it->second;
    } else {
        return omni::core::model::entity::id_to_entities_map ();
    }
}

omni::core::model::entity::id_to_entities_map omni::core::model::entity::getComponents (omni::core::domain domain)
{
    return _components [domain];
}

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

std::map <std::string, std::shared_ptr <omni::core::model::entity>> omni::core::model::entity::getComponentsStartingWith (omni::core::domain domain, std::string name) const
{
    std::map <std::string, std::shared_ptr <omni::core::model::entity>> result;
    auto c = _components.find (domain);
    if (c != _components.end ()) {
        for (auto i : c->second) {
            if (i.first.find (name) == 0) {
                result [i.first] = i.second;
            }
        }
    }
    return result;
}

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
    }
}

bool omni::core::model::entity::removeComponent (omni::core::domain domain, std::shared_ptr <omni::core::model::entity> component)
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

void omni::core::model::entity::clearComponents (omni::core::domain domain)
{
    for (auto i : _components [domain]) {
        i.second->setParent (nullptr);
    }
    _components [domain].clear ();
}

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
**/
void omni::core::model::entity::fillLibraries (std::set <std::string> & libraries)
{
}
