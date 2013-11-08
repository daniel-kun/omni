#include <omni/take2/context.hpp>
#include <omni/take2/block.hpp>
#include <omni/take2/type.hpp>
#include <omni/take2/function.hpp>
#include <omni/take2/context_part.hpp>
#include <omni/take2/return_statement.hpp>
#include <omni/take2/literal_expression.hpp>
#include <omni/take2/builtin_literal.hpp>
#include <omni/take2/function_call_expression.hpp>
#include <omni/take2/expression_statement.hpp>
#include <omni/tests/test_file_manager.hpp>
#include <lld/Driver/Driver.h>
#include <lld/Driver/InputGraph.h>
#include <lld/Driver/WinLinkInputGraph.h>
#include <lld/ReaderWriter/PECOFFLinkingContext.h>
#include <boost/filesystem.hpp>
#include <set>
#include <memory>
#include <iostream>
#ifdef WIN32
#include <Windows.h>
#else
#endif

#define BOOST_TEST_MODULE OmniTake2
#include <boost/test/unit_test.hpp>

namespace {
    /**
    Emits a shared library file with the name fileBaseName.dll. The library exports a function "main" that calls the
    function `func'. That way, it does not matter whether func's linkage_type is external or not.
    Main automatically has the same return type as func. func and main may not take parameters.
    @return The path of the created shared library file.
    **/
    boost::filesystem::path emitSharedLibraryWithFunction (std::shared_ptr <omni::take2::function> func,
                                                           omni::tests::test_file_manager & testFileManager,
                                                           std::string const & fileBaseName)
    {
        using namespace omni::take2;
        // First, add a function that calls the wanted function.
        std::shared_ptr <type> returnType  (func->getReturnType ());
        std::shared_ptr <block> body (new block ());
        std::shared_ptr <expression> callExpression (new function_call_expression (func));
        std::shared_ptr <statement> returnStatement (new return_statement (callExpression));
        body->appendStatement (returnStatement);
        std::shared_ptr <function> caller (new function ("main", returnType, body));
        caller->setLinkageType (linkage_type::external);
        context & c (* func->getContext ());
        c.addFunction (caller);
        std::string sharedLibraryName = testFileManager.getTestFileName (fileBaseName + ".dll").string ();
        c.emitSharedLibraryFile (sharedLibraryName);

        BOOST_CHECK (boost::filesystem::exists(sharedLibraryName));
        return sharedLibraryName;
    }

    /**
    Runs the function `function' and returns it's result in a string representation.
    **/
    template <typename Return>
    Return runFunction (std::shared_ptr <omni::take2::function> func,
                             omni::tests::test_file_manager & testFileManager,
                             std::string const & fileBaseName)
    {
        boost::filesystem::path sharedLibraryPath = emitSharedLibraryWithFunction (func, testFileManager, fileBaseName);
        boost::filesystem::path expPath = sharedLibraryPath;
        boost::filesystem::path libPath = sharedLibraryPath;
        testFileManager.getTestFileName (expPath.replace_extension (".exp").filename ().string ()); // To get rid of the temporary files after the test finishes
        testFileManager.getTestFileName (expPath.replace_extension (".lib").filename ().string ()); // To get rid of the temporary files after the test finishes
        boost::filesystem::path objectFilePath = sharedLibraryPath;
        boost::filesystem::path objectFilePath2 = sharedLibraryPath;
        BOOST_CHECK (! boost::filesystem::exists (objectFilePath.replace_extension (".obj"))); // There shall not be a temporary file anymore
        BOOST_CHECK (! boost::filesystem::exists (objectFilePath2.replace_extension (".o")));   // There shall not be a temporary file anymore
#ifdef WIN32
        HMODULE lib = ::LoadLibraryA (sharedLibraryPath.string ().c_str ());
        HMODULE nullModule = nullptr;
        BOOST_CHECK_NE (lib, nullModule);
        if (lib != nullptr) {
            typedef int (* testFunc) ();
            testFunc f = (testFunc) ::GetProcAddress(lib, "main");
            testFunc nullTestFunc = nullptr;
            BOOST_CHECK_NE (f, nullTestFunc);
            if (f != nullptr) {
                int result = (*f)();
                ::FreeLibrary (lib);
                return result;
            } else {
                ::FreeLibrary (lib);
                throw omni::take2::logic_error (__FILE__, __FUNCTION__, __LINE__,
                                                "Test function could not be found in temporarily created shared object file \"" + sharedLibraryPath.string () + "\".");
            }
        }
        throw omni::take2::logic_error (__FILE__, __FUNCTION__, __LINE__,
                                        "Test shared object could not be loaded: \"" + sharedLibraryPath.string () + "\".");
#else
        throw omni::take2::not_implemented_error (__FILE__, __FUNCTION__, __LINE__);
#endif
    }

}

BOOST_AUTO_TEST_SUITE(contextTests)

BOOST_AUTO_TEST_CASE(ctor)
{
    using namespace omni::take2;
    context c;
}

/**
Creates 20 ids for each domain and checks whether they are unique.
**/
BOOST_AUTO_TEST_CASE(createId)
{
    using namespace omni::take2;
    context c;
    std::set <id> ids;
    for (domain d = domain::first; d < domain::last; d = static_cast <domain> (static_cast <int> (d) + 1)) {
        for (int i = 0; i < 20; ++ i) {
            id id = c.createId (d);
            BOOST_CHECK (ids.find (id) == ids.end ());
            ids.insert (id);
            BOOST_CHECK (ids.find (id) != ids.end ());
        }
    }
}

/**
Tests that a function can be created using createFunction and later be found via findFunctionByName and findPartById.
**/
BOOST_AUTO_TEST_CASE (createAndFindFunction)
{
    using namespace omni::take2;
    context c;
    std::shared_ptr <block> emptyBody (new block ());
    const std::string functionName = "test";
    std::shared_ptr <function> func = c.createFunction (functionName, static_cast <std::shared_ptr <type>> (new type (c, type_class::t_signedInt)), emptyBody);
    
    BOOST_CHECK (func->getName () == functionName);
    
    BOOST_CHECK (c.findFunctionByName (func->getName ()) != nullptr);
    BOOST_CHECK (c.findFunctionByName (func->getName ())->getName () == functionName);

    BOOST_CHECK (c.findFunctionByName (functionName) != nullptr);
    BOOST_CHECK (c.findFunctionByName (functionName)->getName () == functionName);

    BOOST_CHECK (c.findPartById (func->getId ()) != std::shared_ptr <context_part> ());
    BOOST_CHECK (std::dynamic_pointer_cast <function> (c.findPartById (func->getId ()))->getName () == functionName);

}

/**
Tests that a manually created function can be added using addFunction and later be found via findFunctionByName and findPartById.
**/
BOOST_AUTO_TEST_CASE (addAndFindFunction)
{
    using namespace omni::take2;
    context c;
    std::shared_ptr <block> emptyBody (new block ());
    const std::string functionName = "test";
    std::shared_ptr <function> func (new function (functionName, static_cast <std::shared_ptr <type>> (new type (c, type_class::t_signedInt)), emptyBody));

    BOOST_CHECK (func->getContext () == nullptr);

    c.addFunction (func);

    BOOST_CHECK (func->getName () == functionName);
    
    BOOST_CHECK (func->getContext () == & c);

    BOOST_CHECK (c.findFunctionByName (func->getName ()) != nullptr);
    BOOST_CHECK (c.findFunctionByName (func->getName ())->getName () == functionName);

    BOOST_CHECK (c.findFunctionByName (functionName) != nullptr);
    BOOST_CHECK (c.findFunctionByName (functionName)->getName () == functionName);

    BOOST_CHECK (c.findPartById (func->getId ()) != std::shared_ptr <context_part> ());
    BOOST_CHECK (std::dynamic_pointer_cast <function> (c.findPartById (func->getId ()))->getName () == functionName);
}

/**
Tests that a previously added function that is verified to exist in a context can be removed using removeFunction.
**/
BOOST_AUTO_TEST_CASE (removeFunction)
{
    using namespace omni::take2;
    context c;
    std::shared_ptr <block> emptyBody (new block ());
    const std::string functionName = "test";
    std::shared_ptr <function> func = c.createFunction (functionName, static_cast <std::shared_ptr <type>> (new type (c, type_class::t_signedInt)), emptyBody);
    
    BOOST_CHECK (c.findFunctionByName (func->getName ()) != nullptr);
    BOOST_CHECK (c.findFunctionByName (func->getName ())->getName () == functionName);

    
    BOOST_CHECK (c.removeFunction (func));

    BOOST_CHECK (func->getContext () == nullptr);

    BOOST_CHECK (c.findFunctionByName (func->getName ()) == nullptr);
    BOOST_CHECK (c.findFunctionByName (functionName) == nullptr);
}

/**
Writes an assembly (.ll) file and checks, whether it exists.
TODO: Check, whether llvm can interpret the resulting ll file.
**/
BOOST_AUTO_TEST_CASE (emitAssemblyFile)
{
    using namespace omni::take2;
    context c;
    std::shared_ptr <block> body (new block ());
    std::shared_ptr <literal> literal42 (new builtin_literal <signed int> (c, 42));
    std::shared_ptr <expression> literal42exp (new literal_expression (literal42));
    std::shared_ptr <statement> return42 (new return_statement (literal42exp));
    body->appendStatement (return42);
    const std::string functionName = "test";
    std::shared_ptr <function> func = c.createFunction (functionName, static_cast <std::shared_ptr <type>> (new type (c, type_class::t_signedInt)), body);
    omni::tests::test_file_manager testFileManager;
    std::string assemblyFileName = testFileManager.getTestFileName ("emitAssemblyFile.ll").string ();
    c.emitAssemblyFile (assemblyFileName);
    BOOST_CHECK (boost::filesystem::exists(assemblyFileName));
}

/**
Writes an object file (.o on Linux/Unix, .obj on Windows) and checks, whether it exists.
**/
BOOST_AUTO_TEST_CASE (emitObjectFile)
{
    using namespace omni::take2;
    context c;
    std::shared_ptr <block> body (new block ());
    std::shared_ptr <literal> literal42 (new builtin_literal <signed int> (c, 42));
    std::shared_ptr <expression> literal42exp (new literal_expression (literal42));
    std::shared_ptr <statement> return42 (new return_statement (literal42exp));
    body->appendStatement (return42);
    const std::string functionName = "test";
    std::shared_ptr <function> func = c.createFunction (functionName, static_cast <std::shared_ptr <type>> (new type (c, type_class::t_signedInt)), body);
    omni::tests::test_file_manager testFileManager;
    boost::filesystem::path objectFilePath = testFileManager.getTestFileName ("emitObjectFile.obj");
    std::string objectFileName = objectFilePath.string ();
    c.emitObjectFile (objectFileName);
    BOOST_CHECK (boost::filesystem::exists (objectFileName));
}

/**
Writes an shared object file (.so on Linux/Unix, .dll on Windows) and checks, whether it exists, tries to load it and then tries
to call the function exported from it.
**/
BOOST_AUTO_TEST_CASE (emitSharedLibraryFile)
{
    using namespace omni::take2;
    context c;
    std::shared_ptr <block> body (new block ());
    std::shared_ptr <literal> literal42 (new builtin_literal <signed int> (c, 42));
    std::shared_ptr <expression> literal42exp (new literal_expression (literal42));
    std::shared_ptr <statement> return42 (new return_statement (literal42exp));
    body->appendStatement (return42);
    const std::string functionName = "test";
    std::shared_ptr <function> func = c.createFunction (functionName, static_cast <std::shared_ptr <type>> (new type (c, type_class::t_signedInt)), body);
    omni::tests::test_file_manager testFileManager;
    int functionCallResult = runFunction <int> (func, testFileManager, "emitSharedLibraryFile");
    BOOST_CHECK_EQUAL (functionCallResult, 42);
}

BOOST_AUTO_TEST_SUITE_END()
