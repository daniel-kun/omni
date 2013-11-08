#include <omni/take2/function.hpp>
#include <omni/take2/block.hpp>
#include <omni/take2/context.hpp>
#include <omni/take2/type.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (funcionTests)

BOOST_AUTO_TEST_CASE (ctor)
{
    using namespace omni::take2;
    context c;
    std::shared_ptr <type> returnType (new type (c, type_class::t_signedInt));
    function func ("hello", returnType, nullptr);
}

BOOST_AUTO_TEST_SUITE_END ();
