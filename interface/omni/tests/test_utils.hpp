#ifndef OMNI_TESTS_TEST_UTILS_HPP
#define OMNI_TESTS_TEST_UTILS_HPP

#include <omni/tests/test_file_manager.hpp>
#include <omni/core/function_call_expression.hpp>
#include <omni/core/return_statement.hpp>
#include <memory>
#include <string>

#ifdef WIN32
#include <Windows.h>
#else
#endif

namespace omni {
namespace core {
class function;
}
}

namespace omni {
namespace tests {

boost::filesystem::path emitSharedLibraryWithFunction (std::shared_ptr <omni::core::function> func,
                                                       omni::tests::test_file_manager & testFileManager,
                                                       std::string const & fileBaseName,
                                                       std::string & functionName);

template <typename Return>
Return runFunction (std::shared_ptr <omni::core::function> func,
                    omni::tests::test_file_manager & testFileManager,
                    std::string const & fileBaseName);

} // namespace tests
} // namespace omni

/**
Runs the function `function' and returns it's result in a string representation.
**/
template <typename Return>
Return omni::tests::runFunction (std::shared_ptr <omni::core::function> func,
                                 omni::tests::test_file_manager & testFileManager,
                                 std::string const & fileBaseName)
{
    std::string functionName;
    boost::filesystem::path sharedLibraryPath = emitSharedLibraryWithFunction (func, testFileManager, fileBaseName, functionName);
    boost::filesystem::path expPath = sharedLibraryPath;
    boost::filesystem::path libPath = sharedLibraryPath;
    testFileManager.getTestFileName (expPath.replace_extension (".exp").filename ().string ()); // To get rid of the temporary files after the test finishes
    testFileManager.getTestFileName (expPath.replace_extension (".lib").filename ().string ()); // To get rid of the temporary files after the test finishes
    boost::filesystem::path objectFilePath = sharedLibraryPath;
    boost::filesystem::path objectFilePath2 = sharedLibraryPath;
//    BOOST_CHECK (! boost::filesystem::exists (objectFilePath.replace_extension (".obj"))); // There shall not be a temporary file anymore
//    BOOST_CHECK (! boost::filesystem::exists (objectFilePath2.replace_extension (".o")));   // There shall not be a temporary file anymore
#ifdef WIN32
    HMODULE lib = ::LoadLibraryA (sharedLibraryPath.string ().c_str ());
//    HMODULE nullModule = nullptr;
//    BOOST_CHECK_NE (lib, nullModule);
    if (lib != nullptr) {
        typedef int (* testFunc) ();
#pragma warning(push)
#pragma warning(disable:4191)
        testFunc f = reinterpret_cast <testFunc> (::GetProcAddress(lib, functionName.c_str ()));
#pragma warning(pop)
//        testFunc nullTestFunc = nullptr;
//        BOOST_CHECK_NE (f, nullTestFunc);
        if (f != nullptr) {
            Return result = (*f)();
            ::FreeLibrary (lib);
            return result;
        } else {
            ::FreeLibrary (lib);
            throw omni::core::logic_error (__FILE__, __FUNCTION__, __LINE__,
                                            "Test function could not be found in temporarily created shared object file \"" + sharedLibraryPath.string () + "\".");
        }
    }
    throw omni::core::logic_error (__FILE__, __FUNCTION__, __LINE__,
                                    "Test shared object could not be loaded: \"" + sharedLibraryPath.string () + "\".");
#else
    throw omni::core::not_implemented_error (__FILE__, __FUNCTION__, __LINE__);
#endif
}

#endif // include guard
