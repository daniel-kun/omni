#include <omni/core/model/variable_expression.hpp>
#include <omni/core/model/meta_info.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (variableExpressionTests)

BOOST_AUTO_TEST_CASE (metaInfo)
{
    using namespace omni::core::model;

    meta_info & meta = variable_expression::getStaticMetaInfo ();
    BOOST_CHECK_EQUAL (meta.getName (), "variable_expression");
    BOOST_CHECK_EQUAL (meta.getParent (), & pure_expression::getStaticMetaInfo ());
    BOOST_CHECK_EQUAL (meta.getChildCount (), 0u);
}

BOOST_AUTO_TEST_SUITE_END ();
