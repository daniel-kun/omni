#include <omni/take2/function.hpp>
#include <omni/take2/block.hpp>
#include <omni/take2/context.hpp>
#include <omni/take2/type.hpp>

#include <boost/test/unit_test.hpp>

/**
std::vector <std::shared_ptr <parameter>> getParameters () const; // TODO
const std::shared_ptr <block> getBody () const; // TODO
**/

BOOST_AUTO_TEST_SUITE (funcionTests)

BOOST_AUTO_TEST_CASE (ctor)
{
    using namespace omni::take2;
    context c;
    std::shared_ptr <type> returnType (new type (c, type_class::t_signedInt));
    function func ("hello", returnType, nullptr);
}

BOOST_AUTO_TEST_CASE (getReturnType)
{
    using namespace omni::take2;
    context c;
    std::shared_ptr <type> returnType (new type (c, type_class::t_signedInt));
    function func ("hello", returnType, nullptr);
    BOOST_CHECK (func.getReturnType ()->getTypeClass () == type_class::t_signedInt);
}

BOOST_AUTO_TEST_CASE (setLinkageType)
{
    // TODO: Write a function to a shared object file, load it and check whether it was exported or not.
}

BOOST_AUTO_TEST_SUITE_END ();
