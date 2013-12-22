#include <omni/runtime/memory.hpp>

#include <cstdlib>

/**
Allocates new memory and returns a pointer to it. The returned memory's reference counter is set to 1.
@param sizeInBytes Specifies the size of the memory to allocate.
@return Returns a pointer to a newly allocated memory structure of the given size.
**/
void * omni_runtime_memory_alloc (std::size_t sizeInBytes)
{
    reference_count_t * result = reinterpret_cast <reference_count_t *> (std::malloc (sizeInBytes + sizeof (reference_count_t)));
    *result = 1u;
    return ++ result;
}

/**
Increments the reference counter for the specified memory block.
@param memory The memory on which the referene counter should be incremented.
@result Always returns memory.
**/
void * omni_runtime_memory_add_reference (void * memory)
{
    reference_count_t * result = reinterpret_cast <reference_count_t *> (memory);
    ++ (*(result - 1));
    return result;
}

/**
Decrements the reference counter for the specified memory block. If the reference counter reaches 0, the memory block
is deallocated.
@param memory The memory on which the reference counter should be decremented.
@result Returns memory as long as the reference counter is greater than zero. If it reached zero, a nullpointer is returned.
**/
void * omni_runtime_memory_remove_reference (void * memory)
{
    reference_count_t * result = reinterpret_cast <reference_count_t *> (memory);
    // Decrement the memory pointer to access the reference counter.
    -- result;
    if (* result == 1u) {
        // If the reference counter would decrement to 0, free the memory buffer and return a null pointer.
        std::free (result);
        return nullptr;
    }
    -- (*result); // Decrement the reference count.
    return ++ result; // Return the original memory pointer.
}
