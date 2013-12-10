#ifndef OMNI_CORE_CONTEXT_EMIT_OPTIONS_HPP
#define OMNI_CORE_CONTEXT_EMIT_OPTIONS_HPP

#include <omni/core/core.hpp>

#include <boost/filesystem/path.hpp>

#include <vector>

namespace omni {
namespace core {

    /**
    context_emit_options contains several options that the class context uses to emit assembly code (context::emitAssemblyFile), object files (context::emitObjectFile)
    or shared library files (context::emitSharedLibraryFile).
    Options include things like library and include search paths, linker options, options for llvm code generation, etc.
    **/
    class OMNI_CORE_API context_emit_options {
    public:
        context_emit_options ();
        ~ context_emit_options ();
        void addLibrarySearchPath (boost::filesystem::path searchPath);
        std::vector <boost::filesystem::path> getLibrarySearchPaths () const;

    private:
        std::vector <boost::filesystem::path> _librarySearchPaths;
    };
} // namespace core
} // namespace omni

#endif
