#ifndef OMNI_CORE_MODEL_MODULE_HPP
#define OMNI_CORE_MODEL_MODULE_HPP

#include <omni/core/core.hpp>
#include <omni/core/id.hpp>
#include <omni/core/module_emit_options.hpp>
#include <omni/core/model/scope.hpp>

#include <ostream>
#include <memory>
#include <map>

namespace llvm {
    class raw_ostream;
    class Module;
}

namespace omni {
namespace core {
    class context;
}
}

namespace omni {
namespace core {
namespace model {
    class function;

    /**
    A module contains code for a static library, a shared library or an executable.
    See @domain for a list of possible parts of a module.
    **/
    class OMNI_CORE_API module : public scope {
    public:
        module (context & context, std::string name = std::string ());
        module (context & context, id moduleId, std::string name = std::string ());

        domain getDomain () const override;

        context * getContext () override;
        const context * getContext () const override;

        module * getModule () override;
        const module * getModule () const override;

        id createId (domain domain);
        void setEntryPoint (std::shared_ptr <model::function> function);

        void emitAssemblyFile (std::ostream & stream, const module_emit_options & options = module_emit_options ());
        void emitAssemblyFile (llvm::raw_ostream & stream, const module_emit_options & options = module_emit_options ());
        void emitAssemblyFile (std::string const & fileName, const module_emit_options & options = module_emit_options ());
        
        void emitObjectFile (std::ostream & stream, const module_emit_options & options = module_emit_options ());
        void emitObjectFile (llvm::raw_ostream & stream, const module_emit_options & options = module_emit_options ());
        void emitObjectFile (std::string const & fileName, const module_emit_options & options = module_emit_options ());

        void emitSharedLibraryFile (std::ostream & stream, const module_emit_options & options = module_emit_options ());
        void emitSharedLibraryFile (llvm::raw_ostream & stream, const module_emit_options & options = module_emit_options ());
        void emitSharedLibraryFile (std::string const & fileName, const module_emit_options & options = module_emit_options ());

        bool verify (std::string & errorInfo);

        llvm::Module & llvmModule ();

    private:
        std::shared_ptr <llvm::Module> _llvmModule;
        context & _context;
        std::shared_ptr <model::function> _entryPoint;
    };
} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
