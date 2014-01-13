#include <omni/core/model/entity.hpp>
#include <omni/core/context.hpp>

/**
Initializes this entity with an empty name and an invalid id.
The name can be left empty, as long as the actual kind of context part does not require a name.
The id will be set as soon as this context part is added to a context.
**/
omni::core::model::entity::entity () :
    _context (nullptr),
    _name (),
    _id ()
{
}

/**
Initializes this entity with the given name and no context.
**/
omni::core::model::entity::entity (std::string const & name) :
    _context (),
    _name (name),
    _id ()
{
}

omni::core::model::entity::~entity ()
{
}

void omni::core::model::entity::setContext (omni::core::context * context)
{
    _context = context;
}

omni::core::context * omni::core::model::entity::getContext ()
{
    return _context;
}

const omni::core::context * omni::core::model::entity::getContext () const
{
    return _context;
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
