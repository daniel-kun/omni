#ifndef OMNI_CORE_CONTEXT_HPP
#define OMNI_CORE_CONTEXT_HPP

#include <omni/core/core.hpp>
#include <omni/core/domain.hpp>
#include <omni/core/module_emit_options.hpp>
#include <omni/core/id.hpp>
#include <omni/core/model/type_class.hpp>

#include <memory>
#include <string>
#include <map>
#include <utility>

namespace llvm {
    class raw_ostream;
    class LLVMContext;
}

namespace omni {
namespace core {
namespace model {
    class function;
    class function_prototype;
    class type;
    class block;
    class entity;
    class module;
}
}
}

namespace omni {
namespace core {

    /**
    The "context" is an instance of the omni compiler that store some global information about the architecture of the underlying targets
    and a list of modules that are to be emitted when the whole context is emitted.
    **/
    class OMNI_CORE_API context {
    public:
        context ();
        ~ context();

        std::shared_ptr <model::type> sharedBasicType (model::type_class typeClass, int indirectionLevel = 0);

        void addModule (std::shared_ptr <model::module> module);

        const llvm::LLVMContext & llvmContext () const;
        llvm::LLVMContext & llvmContext ();

    private:
        std::unique_ptr <llvm::LLVMContext> _llvmContext;
        std::map <std::pair <model::type_class, int>, std::shared_ptr <model::type>> _sharedBasicTypes;
        std::vector <std::shared_ptr <model::module>> _modules;
    };

} // namespace core
} // namespace omni

#endif // include guard
