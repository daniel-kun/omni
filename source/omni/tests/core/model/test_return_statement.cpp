#include <omni/core/model/return_statement.hpp>
#include <omni/core/model/meta_info.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (returnStatementTests)

BOOST_AUTO_TEST_CASE (metaInfo)
{
    using namespace omni::core::model;

    meta_info & meta = return_statement::getStaticMetaInfo ();
    BOOST_CHECK_EQUAL (meta.getName (), "return_statement");
    BOOST_CHECK_EQUAL (meta.getParent (), & statement::getStaticMetaInfo ());
    BOOST_CHECK_EQUAL (meta.getChildCount (), 0u);
}

BOOST_AUTO_TEST_SUITE_END ();
