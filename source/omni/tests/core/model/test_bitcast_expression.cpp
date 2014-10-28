#include <omni/core/model/bitcast_expression.hpp>
#include <omni/core/model/meta_info.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (bitcastExpressionTests)

BOOST_AUTO_TEST_CASE (metaInfo)
{
    using namespace omni::core::model;

    meta_info & meta = bitcast_expression::getStaticMetaInfo ();
    BOOST_CHECK_EQUAL (meta.getName (), "bitcast_expression");
    BOOST_CHECK_EQUAL (meta.getParent (), & cast_expression::getStaticMetaInfo ());
    BOOST_CHECK_EQUAL (meta.getChildCount (), 0u);
}

BOOST_AUTO_TEST_SUITE_END ();
