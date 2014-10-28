#include <omni/core/model/type.hpp>
#include <omni/core/model/meta_info.hpp>
#include <omni/core/context.hpp>

#include <boost/test/auto_unit_test.hpp>

BOOST_AUTO_TEST_SUITE (typeTests)

BOOST_AUTO_TEST_CASE (metaInfo)
{
    using namespace omni::core;
    using namespace omni::core::model;

    context c;
    type t (c, type_class::t_signedInt);

    meta_info & meta = t.getMetaInfo ();
    BOOST_CHECK_EQUAL (& meta, & type::getStaticMetaInfo ());
    BOOST_CHECK_EQUAL (meta.getName (), "type");
    BOOST_CHECK_EQUAL (meta.getParent (), & entity::getStaticMetaInfo ());
    BOOST_CHECK_EQUAL (meta.getChildCount (), 0u);
}

BOOST_AUTO_TEST_SUITE_END ()
