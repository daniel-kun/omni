#ifndef OMNI_TAKE2_CONTEXT_HPP
#define OMNI_TAKE2_CONTEXT_HPP

#include <omni/take2/take2.hpp>
#include <omni/take2/domain.hpp>
#include <omni/take2/id.hpp>
#include <memory>
#include <string>
#include <map>

namespace llvm {
    class raw_ostream;
    class LLVMContext;
}

namespace omni {
namespace take2 {
    class function;
    class type;
    class block;
    class context_part;

    /**
    The "context" is an instance of the omni compiler that store some global information, caches, etc.
    **/
    class OMNI_TAKE2_API context {
    public:
        context ();
        virtual ~ context ();

        std::shared_ptr <context_part> findPartById (id id);

        id createId (domain domain);
        void setEntryPoint (std::shared_ptr <function> function);

        void emitAssemblyFile (std::ostream & stream);
        void emitAssemblyFile (llvm::raw_ostream & stream);
        void emitAssemblyFile (std::string const & fileName);
        
        void emitObjectFile (std::ostream & stream);
        void emitObjectFile (llvm::raw_ostream & stream);
        void emitObjectFile (std::string const & fileName);

        void emitSharedLibraryFile (std::ostream & stream);
        void emitSharedLibraryFile (llvm::raw_ostream & stream);
        void emitSharedLibraryFile (std::string const & fileName);

        std::shared_ptr <function> createFunction (std::string const & name, std::shared_ptr <type> returnType, std::shared_ptr <block> body);
        std::shared_ptr <function> findFunctionByName (std::string const & name);
        void addFunction (std::shared_ptr <function> function);
        bool removeFunction (std::shared_ptr <function> function);

        const llvm::LLVMContext & llvmContext () const;
        llvm::LLVMContext & llvmContext ();

    private:
        typedef std::map <std::string, std::shared_ptr <context_part>> id_to_parts_map;
        typedef std::map <domain, id_to_parts_map> domain_id_to_parts_map;

        std::unique_ptr <llvm::LLVMContext> _llvmContext;
        std::shared_ptr <function> _entryPoint;
        domain_id_to_parts_map _parts;
    };

} // namespace take2
} // namespace omni

#endif // include guard
