#include <omni/core/model/cast_expression.hpp>
#include <omni/core/model/bitcast_expression.hpp>
#include <omni/core/model/meta_info.hpp>

#include <omni/tests/test_utils.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (castExpressionTests)

BOOST_AUTO_TEST_CASE (metaInfo)
{
    using namespace omni::core::model;

    meta_info & meta = cast_expression::getStaticMetaInfo ();
    BOOST_CHECK_EQUAL (meta.getName (), "cast_expression");
    BOOST_CHECK_EQUAL (meta.getParent (), & pure_expression::getStaticMetaInfo ());
    BOOST_CHECK_EQUAL (meta.getChildCount (), 1u);

    BOOST_CHECK (omni::tests::checkMetaInfoChildren (meta, {
        & bitcast_expression::getStaticMetaInfo ()
    }));
}

BOOST_AUTO_TEST_SUITE_END ();
