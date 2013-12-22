#ifndef OMNI_RUNTIME_MEMORY_HPP
#define OMNI_RUNTIME_MEMORY_HPP

#include <omni/runtime/runtime.hpp>

#include <cstddef>

extern "C" {

typedef std::size_t reference_count_t;

void OMNI_RUNTIME_API * omni_runtime_memory_alloc (std::size_t sizeInBytes);
void OMNI_RUNTIME_API * omni_runtime_memory_add_reference (void * memory);
void OMNI_RUNTIME_API * omni_runtime_memory_remove_reference (void * memory);

}

#endif
