#include <omni/core/context_emit_options.hpp>

omni::core::context_emit_options::context_emit_options () :
    _librarySearchPaths ()
{
}

omni::core::context_emit_options::~ context_emit_options ()
{
}

/**
Adds a path to the library search path that is passed on to the linker.
@see getLibrarySearchPaths()
**/
void omni::core::context_emit_options::addLibrarySearchPath (boost::filesystem::path searchPath)
{
    _librarySearchPaths.push_back (searchPath);
}

/**
Returns a list of library search paths that have been previously added by calling addLibrarySearchPath().
**/
std::vector <boost::filesystem::path> omni::core::context_emit_options::getLibrarySearchPaths () const
{
    return _librarySearchPaths;
}
