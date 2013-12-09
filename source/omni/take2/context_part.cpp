#include <omni/take2/context_part.hpp>
#include <omni/take2/context.hpp>


/**
Initializes this context part with an empty name and an invalid id.
The name can be left empty, as long as the actual kind of context part does not require a name.
The id will be set as soon as this context part is added to a context.
**/
omni::take2::context_part::context_part () :
    _context (nullptr),
    _name (),
    _id ()
{
}

omni::take2::context_part::context_part (std::string const & name) :
    _context (nullptr),
    _name (name),
    _id ()
{
}

omni::take2::context_part::~context_part ()
{
}

void omni::take2::context_part::setContext (omni::take2::context * context)
{
    _context = context;
}

omni::take2::context * omni::take2::context_part::getContext ()
{
    return _context;
}

const omni::take2::context * omni::take2::context_part::getContext () const
{
    return _context;
}

std::string omni::take2::context_part::getName () const
{
    return _name;
}

void omni::take2::context_part::setName (const std::string & name)
{
    _name = name;
}

void omni::take2::context_part::setId (omni::take2::id newId)
{
    _id = newId;
}

omni::take2::id omni::take2::context_part::getId () const
{
    return _id;
}

/**
Can be overridden by specific context_parts.
Overrides can add entries to 'libraries'. These entries will be added to the linker when @see context::emitSharedLibraryFile is used to create
a shared library file.
**/
void omni::take2::context_part::fillLibraries (std::set <std::string> & libraries)
{
}
