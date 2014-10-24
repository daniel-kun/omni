#ifndef OMNI_CORE_MODULE_EMIT_OPTIONS_HPP
#define OMNI_CORE_MODULE_EMIT_OPTIONS_HPP

#include <omni/core/core.hpp>

#ifndef Q_MOC_RUN
#include <boost/filesystem/path.hpp>
#endif

#include <vector>
#include <set>

namespace omni {
namespace core {

    /**
    module_emit_options contains several options that the class context uses to emit assembly code (context::emitAssemblyFile), object files (context::emitObjectFile)
    or shared library files (context::emitSharedLibraryFile).
    Options include things like library and include search paths, linker options, options for llvm code generation, etc.
    **/
    class OMNI_CORE_API module_emit_options {
    public:
        module_emit_options ();
        ~ module_emit_options ();
        void addLibrarySearchPath (boost::filesystem::path searchPath);
        std::vector <boost::filesystem::path> getLibrarySearchPaths () const;

        void addLibrary (std::string library);
        std::set <std::string> getLibraries () const;

    private:
        std::vector <boost::filesystem::path> _librarySearchPaths;
        std::set <std::string> _libraries;
    };
} // namespace core
} // namespace omni

#endif
