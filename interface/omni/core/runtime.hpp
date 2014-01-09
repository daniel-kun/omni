#ifndef OMNI_CORE_RUNTIME_HPP
#define OMNI_CORE_RUNTIME_HPP

#include <omni/core/core.hpp>

#include <memory>

namespace omni {
namespace core {
    class module;
    class external_function;

    /**
    Manages the functions and structures provided by the omni runtime.
    Use omni::core::module::getRuntime() to access it in a specific module.
    TODO: This should be implemented by parsing the omni runtime headers using clang.
    **/
    class OMNI_CORE_API runtime {
    public:
        runtime (module & module);

        std::shared_ptr <external_function> getMemoryAllocate ();
        std::shared_ptr <external_function> getMemoryAddReference ();
        std::shared_ptr <external_function> getMemoryRemoveReference ();

    private:
        module & _module;
        std::shared_ptr <external_function> _memoryAllocate;
        std::shared_ptr <external_function> _memoryAddReference;
        std::shared_ptr <external_function> _memoryRemoveReference;
    };

} // namespace core
} // namespace omni

#endif // include guard
