#include <omni/core/module_emit_options.hpp>

omni::core::module_emit_options::module_emit_options () :
    _librarySearchPaths (),
    _libraries ()
{
}

omni::core::module_emit_options::~ module_emit_options ()
{
}

/**
Adds a path to the library search path that is passed on to the linker.
@see getLibrarySearchPaths()
**/
void omni::core::module_emit_options::addLibrarySearchPath (boost::filesystem::path searchPath)
{
    _librarySearchPaths.push_back (searchPath);
}

/**
Returns a list of library search paths that have been previously added by calling addLibrarySearchPath().
@see addLibrarySearchPath()
**/
std::vector <boost::filesystem::path> omni::core::module_emit_options::getLibrarySearchPaths () const
{
    return _librarySearchPaths;
}

/**
Adds a library that will be linked into the executable or shared object file by passing it to the linker.
@see getLibraries()
**/
void omni::core::module_emit_options::addLibrary (std::string library)
{
    if (_libraries.find (library) == _libraries.end ()) {
        _libraries.insert (library);
    }
}

/**
Returns a set of libraries that have been previously added by calling addLibrary().
@see addLibrary().
**/
std::set <std::string> omni::core::module_emit_options::getLibraries () const
{
    return _libraries;
}
