#include <omni/core/model/expression.hpp>
#include <omni/core/model/pure_expression.hpp>
#include <omni/core/model/modifying_expression.hpp>
#include <omni/core/model/meta_info.hpp>

#include <omni/tests/test_utils.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (expressionTests)

BOOST_AUTO_TEST_CASE (metaInfo)
{
    using namespace omni::core::model;

    meta_info & meta = expression::getStaticMetaInfo ();
    BOOST_CHECK_EQUAL (meta.getName (), "expression");
    BOOST_CHECK_EQUAL (meta.getParent (), & statement::getStaticMetaInfo ());
    BOOST_CHECK_EQUAL (meta.getChildCount (), 2u);

    BOOST_CHECK (omni::tests::checkMetaInfoChildren (meta, {
        & pure_expression::getStaticMetaInfo (),
        & modifying_expression::getStaticMetaInfo ()
    }));
}

BOOST_AUTO_TEST_SUITE_END ();
