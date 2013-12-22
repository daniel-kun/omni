#include <omni/runtime/memory.hpp>

#include <boost/test/auto_unit_test.hpp>

BOOST_AUTO_TEST_SUITE (runtimeMemoryTests)

BOOST_AUTO_TEST_CASE (referenceCounting)
{
    const std::size_t memorySize = 100u;
    void * memory = omni_runtime_memory_alloc (memorySize);
    char * buffer = reinterpret_cast <char *> (memory);
    // Check whether we can write all memory slots that should have been allocated:
    for (char * p = buffer; p < buffer + memorySize; ++ p) {
        * p = 'A';
    }
    BOOST_CHECK_EQUAL (std::string (memorySize, 'A'), std::string (buffer, memorySize));
    BOOST_CHECK (omni_runtime_memory_add_reference (memory) == memory);
    BOOST_CHECK (omni_runtime_memory_remove_reference (memory) == memory);
    BOOST_CHECK (omni_runtime_memory_remove_reference (memory) == nullptr);
}

BOOST_AUTO_TEST_SUITE_END ()
