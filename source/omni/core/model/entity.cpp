#include <omni/core/model/entity.hpp>
#include <omni/core/model/scope.hpp>
#include <omni/core/model/module.hpp>
#include <omni/core/context.hpp>

/**
Initializes this entity with an empty name and an invalid id.
The name can be left empty, as long as the actual kind of context part does not require a name.
The id will be set as soon as this context part is added to a context.
**/
omni::core::model::entity::entity (omni::core::model::scope * parent) :
    _parent (parent),
    _name (),
    _id ()
{
}

/**
Initializes this entity within the given parent and with the given name.
**/
omni::core::model::entity::entity (omni::core::model::scope * parent, std::string const & name) :
    _parent (parent),
    _name (name),
    _id ()
{
}

/**
Initializes this entity within the given parent and with the given id and name.
**/
omni::core::model::entity::entity (omni::core::model::scope * parent, omni::core::id entityId, std::string const & name) :
    _parent (parent),
    _name (name),
    _id (entityId)
{
}

omni::core::model::entity::~entity ()
{
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

/**
Can be overridden by specific entities.
Overrides can add entries to 'libraries'. These entries will be added to the linker when @see context::emitSharedLibraryFile is used to create
a shared library file.
**/
void omni::core::model::entity::fillLibraries (std::set <std::string> & libraries)
{
}
