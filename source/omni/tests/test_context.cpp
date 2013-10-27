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
#include <boost/filesystem.hpp>
#include <set>

#define BOOST_TEST_MODULE OmniTake2
#include <boost/test/unit_test.hpp>

namespace {
    /**
    Returns an absolute path to the temporary test file named testFileName.
    Test files are stored in the directory test/ in the project root.
    **/
    boost::filesystem::path buildTestFilePath (std::string const & testFileName)
    {
        boost::filesystem::path path = boost::filesystem::current_path ().parent_path ();
        path /= boost::filesystem::path ("test") /= testFileName;
        return path;
    }

    /**
    Runs the function `function' and returns it's result. The template parameter must match
    the function's return type.
    **/
    void runFunction (std::shared_ptr <omni::take2::function> func, std::string const & temporaryAssemblyFileName)
    {
        using namespace omni::take2;
        // First, add a function that calls the wanted function.
        std::shared_ptr <type> returnType  (new type (* func->getContext (), type_class::t_signedInt));
        std::shared_ptr <block> body (new block ());
        std::shared_ptr <expression> callExpression (new function_call_expression (func));
        std::shared_ptr <statement> returnStatement (new return_statement (callExpression));
        body->appendStatement (returnStatement);
        std::shared_ptr <function> caller (new function ("main", returnType, body));
        context & c (* func->getContext ());
        c.addFunction (caller);
        c.emitAssemblyFile (buildTestFilePath (temporaryAssemblyFileName).string ());
    }
}

BOOST_AUTO_TEST_SUITE(contextTests)

    /*
        void setEntryPoint (std::shared_ptr <function> function);
        void emitAssemblyFile (std::string const & fileName);
    */

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
    //c.emitAssemblyFile (buildTestFilePath ("emitAssemblyFile.ll").string ());
    runFunction (func, "emitAssemblyFile.ll");
}

BOOST_AUTO_TEST_SUITE_END()
