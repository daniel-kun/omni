#include <omni/core/model/modifying_expression.hpp>
#include <omni/core/model/function_call_expression.hpp>
#include <omni/core/model/variable_assignment_expression.hpp>
#include <omni/core/model/meta_info.hpp>

#include <omni/tests/test_utils.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (modifyingExpressionTests)

BOOST_AUTO_TEST_CASE (metaInfo)
{
    using namespace omni::core::model;

    meta_info & meta = modifying_expression::getStaticMetaInfo ();
    BOOST_CHECK_EQUAL (meta.getName (), "modifying_expression");
    BOOST_CHECK_EQUAL (meta.getParent (), & expression::getStaticMetaInfo ());
    BOOST_CHECK_EQUAL (meta.getChildCount (), 2u);

    BOOST_CHECK (omni::tests::checkMetaInfoChildren (meta, {
        & function_call_expression::getStaticMetaInfo (),
        & variable_assignment_expression::getStaticMetaInfo ()
    }));
}

BOOST_AUTO_TEST_SUITE_END ();
