#include <omni/core/model/pure_expression.hpp>
#include <omni/core/model/binary_operator_expression.hpp>
#include <omni/core/model/cast_expression.hpp>
#include <omni/core/model/literal_expression.hpp>
#include <omni/core/model/variable_declaration_expression.hpp>
#include <omni/core/model/variable_expression.hpp>
#include <omni/core/model/meta_info.hpp>

#include <omni/tests/test_utils.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (pureExpressionTests)

BOOST_AUTO_TEST_CASE (metaInfo)
{
    using namespace omni::core::model;

    meta_info & meta = pure_expression::getStaticMetaInfo ();
    BOOST_CHECK_EQUAL (meta.getName (), "pure_expression");
    BOOST_CHECK_EQUAL (meta.getParent (), & expression::getStaticMetaInfo ());
    BOOST_CHECK_EQUAL (meta.getChildCount (), 5u);

    BOOST_CHECK (omni::tests::checkMetaInfoChildren (meta, {
        & binary_operator_expression::getStaticMetaInfo (),
        & cast_expression::getStaticMetaInfo (),
        & literal_expression::getStaticMetaInfo (),
        & variable_declaration_expression::getStaticMetaInfo (),
        & variable_expression::getStaticMetaInfo ()
    }));
}

BOOST_AUTO_TEST_SUITE_END ();
