#ifndef OMNI_CODE_MODULE_HPP
#define OMNI_CODE_MODULE_HPP

#include <omni/core/core.hpp>
#include <omni/core/id.hpp>
#include <omni/core/context_emit_options.hpp>

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
    class type;
    class context_part;
    class function_prototype;
    class function;
    class block;

    /**
    A module contains code for a static library, a shared library or an executable.
    See @domain for a list of possible parts of a module.
    **/
    class OMNI_CORE_API module {
    public:
        module (context & context, std::string name = std::string ());
        module (context & context, id moduleId, std::string name = std::string ());

        context & getContext ();
        const context & getContext () const;

        std::shared_ptr <context_part> findPartById (id id);

        id createId (domain domain);
        void setEntryPoint (std::shared_ptr <function> function);

        void emitAssemblyFile (std::ostream & stream, const context_emit_options & options = context_emit_options ());
        void emitAssemblyFile (llvm::raw_ostream & stream, const context_emit_options & options = context_emit_options ());
        void emitAssemblyFile (std::string const & fileName, const context_emit_options & options = context_emit_options ());
        
        void emitObjectFile (std::ostream & stream, const context_emit_options & options = context_emit_options ());
        void emitObjectFile (llvm::raw_ostream & stream, const context_emit_options & options = context_emit_options ());
        void emitObjectFile (std::string const & fileName, const context_emit_options & options = context_emit_options ());

        void emitSharedLibraryFile (std::ostream & stream, const context_emit_options & options = context_emit_options ());
        void emitSharedLibraryFile (llvm::raw_ostream & stream, const context_emit_options & options = context_emit_options ());
        void emitSharedLibraryFile (std::string const & fileName, const context_emit_options & options = context_emit_options ());

        std::shared_ptr <function> createFunction (std::string const & name, std::shared_ptr <type> returnType, std::shared_ptr <block> body);
        std::shared_ptr <function_prototype> findFunctionByName (std::string const & name);
        void addFunction (std::shared_ptr <function_prototype> function);
        bool removeFunction (std::shared_ptr <function_prototype> function);

        bool verify (std::string & errorInfo);

        llvm::Module & llvmModule ();

    private:
        typedef std::map <std::string, std::shared_ptr <context_part>> id_to_parts_map;
        typedef std::map <domain, id_to_parts_map> domain_id_to_parts_map;

        std::shared_ptr <llvm::Module> _llvmModule;
        context & _context;
        id _id;
        std::string _name;
        std::shared_ptr <function> _entryPoint;
        domain_id_to_parts_map _parts;
    };
}
}

#endif // include guard
