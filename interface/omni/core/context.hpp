#ifndef OMNI_CORE_CONTEXT_HPP
#define OMNI_CORE_CONTEXT_HPP

#include <omni/core/core.hpp>
#include <omni/core/domain.hpp>
#include <omni/core/type_class.hpp>
#include <omni/core/context_emit_options.hpp>
#include <omni/core/id.hpp>

#include <memory>
#include <string>
#include <map>

namespace llvm {
    class raw_ostream;
    class LLVMContext;
}

namespace omni {
namespace core {
    class function;
    class function_prototype;
    class type;
    class block;
    class context_part;

    /**
    The "context" is an instance of the omni compiler that store some global information, caches, etc.
    **/
    class OMNI_CORE_API context {
    public:
        context ();
        virtual ~ context ();

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

        std::shared_ptr <type> sharedType (type_class typeClass);

        const llvm::LLVMContext & llvmContext () const;
        llvm::LLVMContext & llvmContext ();

    private:
        typedef std::map <std::string, std::shared_ptr <context_part>> id_to_parts_map;
        typedef std::map <domain, id_to_parts_map> domain_id_to_parts_map;

        std::unique_ptr <llvm::LLVMContext> _llvmContext;
        std::shared_ptr <function> _entryPoint;
        std::map <type_class, std::shared_ptr <type>> _sharedTypes;
        domain_id_to_parts_map _parts;
    };

} // namespace core
} // namespace omni

#endif // include guard
