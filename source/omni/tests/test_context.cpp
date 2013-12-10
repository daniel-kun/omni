#include <omni/core/context.hpp>
#include <omni/core/block.hpp>
#include <omni/core/type.hpp>
#include <omni/core/function.hpp>
#include <omni/core/context_part.hpp>
#include <omni/core/return_statement.hpp>
#include <omni/core/literal_expression.hpp>
#include <omni/core/builtin_literal.hpp>
#include <omni/core/function_call_expression.hpp>
#include <omni/core/expression_statement.hpp>
#include <omni/tests/test_file_manager.hpp>
#include <omni/tests/test_utils.hpp>
#include <set>
#include <memory>
#include <iostream>

#define BOOST_TEST_MODULE OmniCore
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(contextTests)

BOOST_AUTO_TEST_CASE(ctor)
{
    using namespace omni::core;
    context c;
}

/**
Creates 20 ids for each domain and checks whether they are unique.
**/
BOOST_AUTO_TEST_CASE(createId)
{
    using namespace omni::core;
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
    using namespace omni::core;
    context c;
    std::shared_ptr <block> emptyBody (new block ());
    const std::string functionName = "test";
    std::shared_ptr <function> func = c.createFunction (functionName, static_cast <std::shared_ptr <type>> (type::sharedType (c, type_class::t_signedInt)), emptyBody);
    
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
    using namespace omni::core;
    context c;
    std::shared_ptr <block> emptyBody (new block ());
    const std::string functionName = "test";
    std::shared_ptr <function> func (new function (functionName, static_cast <std::shared_ptr <type>> (type::sharedType (c, type_class::t_signedInt)), emptyBody));

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
    using namespace omni::core;
    context c;
    std::shared_ptr <block> emptyBody (new block ());
    const std::string functionName = "test";
    std::shared_ptr <function> func = c.createFunction (functionName, static_cast <std::shared_ptr <type>> (type::sharedType (c, type_class::t_signedInt)), emptyBody);
    
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
    using namespace omni::core;
    context c;
    std::shared_ptr <block> body (new block ());
    std::shared_ptr <literal> literal42 (new builtin_literal <signed int> (c, 42));
    std::shared_ptr <expression> literal42exp (new literal_expression (literal42));
    std::shared_ptr <statement> return42 (new return_statement (literal42exp));
    body->appendStatement (return42);
    const std::string functionName = "test";
    std::shared_ptr <function> func = c.createFunction (functionName, static_cast <std::shared_ptr <type>> (type::sharedType (c, type_class::t_signedInt)), body);
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
    using namespace omni::core;
    context c;
    std::shared_ptr <block> body (new block ());
    std::shared_ptr <literal> literal42 (new builtin_literal <signed int> (c, 42));
    std::shared_ptr <expression> literal42exp (new literal_expression (literal42));
    std::shared_ptr <statement> return42 (new return_statement (literal42exp));
    body->appendStatement (return42);
    const std::string functionName = "test";
    std::shared_ptr <function> func = c.createFunction (functionName, static_cast <std::shared_ptr <type>> (type::sharedType (c, type_class::t_signedInt)), body);
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
    using namespace omni::core;
    context c;
    std::shared_ptr <block> body (new block ());
    std::shared_ptr <literal> literal42 (new builtin_literal <signed int> (c, 42));
    std::shared_ptr <expression> literal42exp (new literal_expression (literal42));
    std::shared_ptr <statement> return42 (new return_statement (literal42exp));
    body->appendStatement (return42);
    const std::string functionName = "test";
    std::shared_ptr <function> func = c.createFunction (functionName, static_cast <std::shared_ptr <type>> (type::sharedType (c, type_class::t_signedInt)), body);
    omni::tests::test_file_manager testFileManager;
    int functionCallResult = omni::tests::runFunction <int> (func, testFileManager, "emitSharedLibraryFile");
    BOOST_CHECK_EQUAL (functionCallResult, 42);
}

BOOST_AUTO_TEST_SUITE_END()
