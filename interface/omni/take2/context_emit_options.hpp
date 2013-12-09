#ifndef OMNI_TAKE2_CONTEXT_EMIT_OPTIONS_HPP
#define OMNI_TAKE2_CONTEXT_EMIT_OPTIONS_HPP

#include <omni/take2/take2.hpp>

#include <boost/filesystem/path.hpp>

#include <vector>

namespace omni {
namespace take2 {

    /**
    context_emit_options contains several options that the class context uses to emit assembly code (context::emitAssemblyFile), object files (context::emitObjectFile)
    or shared library files (context::emitSharedLibraryFile).
    Options include things like library and include search paths, linker options, options for llvm code generation, etc.
    **/
    class OMNI_TAKE2_API context_emit_options {
    public:
        context_emit_options ();
        ~ context_emit_options ();
        void addLibrarySearchPath (boost::filesystem::path searchPath);
        std::vector <boost::filesystem::path> getLibrarySearchPaths () const;

    private:
        std::vector <boost::filesystem::path> _librarySearchPaths;
    };
} // namespace take2
} // namespace omni

#endif
