#include <omni/core/model/literal_expression.hpp>
#include <omni/core/model/builtin_literal_expression.hpp>
#include <omni/core/model/meta_info.hpp>

#include <omni/tests/test_utils.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (literalExpressionTests)

BOOST_AUTO_TEST_CASE (metaInfo)
{
    using namespace omni::core::model;

    meta_info & meta = literal_expression::getStaticMetaInfo ();
    BOOST_CHECK_EQUAL (meta.getName (), "literal_expression");
    BOOST_CHECK_EQUAL (meta.getParent (), & pure_expression::getStaticMetaInfo ());
    BOOST_CHECK_EQUAL (meta.getChildCount (), 1u);

    BOOST_CHECK (omni::tests::checkMetaInfoChildren (meta, {
        & builtin_literal_expression <int>::getStaticMetaInfo ()
    }));
}

BOOST_AUTO_TEST_SUITE_END ();
