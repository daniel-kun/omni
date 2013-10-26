#include <omni/take2/context.hpp>
#include <omni/take2/block.hpp>
#include <omni/take2/type.hpp>
#include <omni/take2/function.hpp>
#include <omni/take2/context_part.hpp>
#define BOOST_TEST_MODULE OmniTake2
#include <boost/test/unit_test.hpp>
#include <set>

BOOST_AUTO_TEST_SUITE(contextTests)

    /*
        std::shared_ptr <context_part> findPartById (id id);

-        id createId (domain domain);
        void setEntryPoint (std::shared_ptr <function> function);
        void emitAssemblyFile (std::string const & fileName);

-        std::shared_ptr <function> createFunction (std::string const & name, std::shared_ptr <type> returnType, std::shared_ptr <block> body);
-        std::shared_ptr <function> findFunctionByName (std::string const & name);
        void addFunction (std::shared_ptr <function> function);
        bool removeFunction (std::shared_ptr <function> function);
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
Tests that a function can be created using createFunction and later be found via findFunctionByName and findPartById
-        std::shared_ptr <function> createFunction (std::string const & name, std::shared_ptr <type> returnType, std::shared_ptr <block> body);
-        std::shared_ptr <function> findFunctionByName (std::string const & name);
**/
BOOST_AUTO_TEST_CASE (createAndFindFunction)
{
    using namespace omni::take2;
    context c;
    std::shared_ptr <block> emptyBody (new block ());
    const std::string functionName = "test";
    std::shared_ptr <function> func = c.createFunction (functionName, static_cast <std::shared_ptr <type>> (new type (type_class::t_signedInt)), emptyBody);
    
    BOOST_CHECK (func->getName () == functionName);
    
    BOOST_CHECK (c.findFunctionByName (func->getName ()) != nullptr);
    BOOST_CHECK (c.findFunctionByName (func->getName ())->getName () == functionName);

    BOOST_CHECK (c.findFunctionByName (functionName) != nullptr);
    BOOST_CHECK (c.findFunctionByName (functionName)->getName () == functionName);

    BOOST_CHECK (c.findPartById (func->getId ()) != std::shared_ptr <context_part> ());
    BOOST_CHECK (std::dynamic_pointer_cast <function> (c.findPartById (func->getId ()))->getName () == functionName);

}

BOOST_AUTO_TEST_SUITE_END()
