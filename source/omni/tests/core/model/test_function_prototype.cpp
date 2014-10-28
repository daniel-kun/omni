#include <omni/core/context.hpp>
#include <omni/core/model/meta_info.hpp>
#include <omni/core/model/module.hpp>
#include <omni/core/model/function_prototype.hpp>
#include <omni/core/model/function.hpp>
#include <omni/core/model/external_function.hpp>

#include <omni/tests/test_utils.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (funcionPrototypeTests)

BOOST_AUTO_TEST_CASE (metaInfo)
{
    using namespace omni::core::model;

    meta_info & meta = function_prototype::getStaticMetaInfo ();
    BOOST_CHECK_EQUAL (meta.getName (), "function_prototype");
    BOOST_CHECK_EQUAL (meta.getParent (), & scope::getStaticMetaInfo ());
    BOOST_CHECK_EQUAL (meta.getChildCount (), 2u);

    BOOST_CHECK (omni::tests::checkMetaInfoChildren (meta, {
        & function::getStaticMetaInfo (),
        & external_function::getStaticMetaInfo ()
    }));

}

BOOST_AUTO_TEST_SUITE_END ();
