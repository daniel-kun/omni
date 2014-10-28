#include <omni/core/model/statement.hpp>
#include <omni/core/model/meta_info.hpp>
#include <omni/core/model/block.hpp>
#include <omni/core/model/expression.hpp>
#include <omni/core/model/if_statement.hpp>
#include <omni/core/model/return_statement.hpp>
#include <omni/core/model/while_statement.hpp>
#include <omni/core/model/do_while_statement.hpp>

#include <omni/tests/test_utils.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (statementTests)

BOOST_AUTO_TEST_CASE (metaInfo)
{
    using namespace omni::core::model;

    meta_info & meta = statement::getStaticMetaInfo ();
    BOOST_CHECK_EQUAL (meta.getName (), "statement");
    BOOST_CHECK_EQUAL (meta.getParent (), & scope::getStaticMetaInfo ());
    BOOST_CHECK_EQUAL (meta.getChildCount (), 6u);

    BOOST_CHECK (omni::tests::checkMetaInfoChildren (meta, {
        & block::getStaticMetaInfo (),
        & expression::getStaticMetaInfo (),
        & if_statement::getStaticMetaInfo (),
        & return_statement::getStaticMetaInfo (),
        & while_statement::getStaticMetaInfo (),
        & do_while_statement::getStaticMetaInfo ()
    }));
}

BOOST_AUTO_TEST_SUITE_END ();
