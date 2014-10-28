#include <omni/core/model/scope.hpp>
#include <omni/core/model/meta_info.hpp>
#include <omni/core/model/function_prototype.hpp>
#include <omni/core/model/module.hpp>
#include <omni/core/model/parameter.hpp>
#include <omni/core/model/statement.hpp>
#include <omni/core/context.hpp>

#include <omni/tests/test_utils.hpp>

#include <boost/test/auto_unit_test.hpp>

BOOST_AUTO_TEST_SUITE (scopeTests)

BOOST_AUTO_TEST_CASE (metaInfo)
{
    using namespace omni::core;
    using namespace omni::core::model;

    meta_info & meta = scope::getStaticMetaInfo ();
    BOOST_CHECK_EQUAL (meta.getName (), "scope");
    BOOST_CHECK_EQUAL (meta.getParent (), & entity::getStaticMetaInfo ());
    BOOST_CHECK_EQUAL (meta.getChildCount (), 4u);

    BOOST_CHECK (omni::tests::checkMetaInfoChildren (meta, {
        & function_prototype::getStaticMetaInfo (),
        & module::getStaticMetaInfo (),
        & parameter::getStaticMetaInfo (),
        & statement::getStaticMetaInfo (),
    }));
}

BOOST_AUTO_TEST_SUITE_END ()
