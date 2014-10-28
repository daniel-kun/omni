#include <omni/core/model/builtin_literal_expression.hpp>
#include <omni/core/model/meta_info.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (builtinLiteralExpressionTests)

BOOST_AUTO_TEST_CASE (metaInfo)
{
    using namespace omni::core::model;

    meta_info & meta = builtin_literal_expression <int>::getStaticMetaInfo ();
    BOOST_CHECK_EQUAL (meta.getName (), "builtin_literal_expression");
    BOOST_CHECK_EQUAL (meta.getParent (), & literal_expression::getStaticMetaInfo ());
    BOOST_CHECK_EQUAL (meta.getChildCount (), 0u);
}

BOOST_AUTO_TEST_SUITE_END ();
