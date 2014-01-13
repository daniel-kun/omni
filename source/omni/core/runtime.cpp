#include <omni/core/runtime.hpp>
#include <omni/core/context.hpp>
#include <omni/core/module.hpp>
#include <omni/core/type.hpp>
#include <omni/core/type_class.hpp>
#include <omni/core/parameter.hpp>
#include <omni/core/external_function.hpp>

/**
Initializes this runtime for the given module.
**/
omni::core::runtime::runtime (module & module) :
    _module (module),
    _memoryAllocate (),
    _memoryAddReference (),
    _memoryRemoveReference ()
{
}

/**
Returns an external_function describing the Omni Runtime function void * omni_runtime_memory_allocate(std::size_t sizeInBytes).
**/
std::shared_ptr <omni::core::model::external_function> omni::core::runtime::getMemoryAllocate ()
{
    if (_memoryAllocate == nullptr) {
        context & c (_module.getContext ());
        _memoryAllocate.reset (
            new model::external_function (
                _module,
                "omni-runtime.lib",
                "omni_runtime_memory_allocate",
                c.sharedBasicType (model::type_class::t_unsignedByte, 1),
                std::vector <std::shared_ptr <model::parameter>> {
                    static_cast <std::shared_ptr <model::parameter>> (new model::parameter (c.sharedBasicType (model::type_class::t_unsignedInt), "sizeInBytes"))
                }));
        _module.addFunction (_memoryAllocate);
    }
    return _memoryAllocate;
}

/**
Returns an external_function describing the Omni Runtime function void * omni_runtime_add_allocate(void * memory).
**/
std::shared_ptr <omni::core::model::external_function> omni::core::runtime::getMemoryAddReference ()
{
    if (_memoryAddReference == nullptr) {
        context & c (_module.getContext ());
        _memoryAddReference.reset (
            new model::external_function (
                _module,
                "omni-runtime.lib",
                "omni_runtime_memory_add_reference",
                c.sharedBasicType (model::type_class::t_unsignedByte, 1),
                std::vector <std::shared_ptr <model::parameter>> {
                    static_cast <std::shared_ptr <model::parameter>> (new model::parameter (c.sharedBasicType (model::type_class::t_unsignedByte, 1), "memory"))
                }));
        _module.addFunction (_memoryAddReference);
    }
    return _memoryAddReference;
}

/**
Returns an external_function describing the Omni Runtime function void * omni_runtime_add_allocate(void * memory).
**/
std::shared_ptr <omni::core::model::external_function> omni::core::runtime::getMemoryRemoveReference ()
{
    if (_memoryRemoveReference == nullptr) {
        context & c (_module.getContext ());
        _memoryRemoveReference.reset (
            new model::external_function (
                _module,
                "omni-runtime.lib",
                "omni_runtime_memory_remove_reference",
                c.sharedBasicType (model::type_class::t_unsignedByte, 1),
                std::vector <std::shared_ptr <model::parameter>> {
                    static_cast <std::shared_ptr <model::parameter>> (new model::parameter (c.sharedBasicType (model::type_class::t_unsignedByte, 1), "memory"))
                }));
        _module.addFunction (_memoryRemoveReference);
    }
    return _memoryRemoveReference;
}
