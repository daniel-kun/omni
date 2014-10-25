#include <omni/core/model/meta_info.hpp>

#include <boost/test/auto_unit_test.hpp>

#include <memory>

BOOST_AUTO_TEST_SUITE (metaInfoTests)

BOOST_AUTO_TEST_CASE (ctor1)
{
    using namespace omni::core::model;
    meta_info m ("hello");
    BOOST_CHECK_EQUAL (m.getName (), "hello");
    BOOST_CHECK (m.getParent () == nullptr);
    BOOST_CHECK_EQUAL (m.getChildCount (), 0u);
    BOOST_CHECK (m.getExtension ("foo") == nullptr);
}

BOOST_AUTO_TEST_CASE (ctor2_getName_getParent_getChildAt_getChildCount)
{
    using namespace omni::core::model;
    meta_info parent ("parent");
    meta_info m (parent, "hello");
    BOOST_CHECK_EQUAL (m.getName (), "hello");
    BOOST_CHECK (m.getParent () == & parent);
    BOOST_CHECK_EQUAL (parent.getChildCount (), 1u);
    BOOST_CHECK_EQUAL (& parent.getChildAt (0u), & m);
    BOOST_CHECK_EQUAL (m.getChildCount (), 0u);
    BOOST_CHECK (m.getExtension ("foo") == nullptr);
}

BOOST_AUTO_TEST_CASE (getChildAt_getChildCount)
{
    using namespace omni::core::model;
    meta_info parent ("parent");
    meta_info m1 (parent, "child1");
    meta_info m2 (parent, "child2");
    meta_info m3 (parent, "child3");

    BOOST_CHECK (parent.getParent () == nullptr);
    BOOST_CHECK (m1.getParent () == & parent);
    BOOST_CHECK (m2.getParent () == & parent);
    BOOST_CHECK (m3.getParent () == & parent);
    BOOST_CHECK_EQUAL (parent.getChildCount (), 3u);
    BOOST_CHECK_EQUAL (& parent.getChildAt (0u), & m1);
    BOOST_CHECK_EQUAL (& parent.getChildAt (1u), & m2);
    BOOST_CHECK_EQUAL (& parent.getChildAt (2u), & m3);
}

BOOST_AUTO_TEST_CASE (setExtension_getExtension)
{
    using namespace omni::core::model;
    meta_info m ("extendable");

    class test_extension : public meta_info_extension {
    public:
        test_extension (int foo) : _foo (foo) { }
        int _foo;
    };

    auto ext1 = std::make_shared <test_extension> (-1);
    auto ext2 = std::make_shared <test_extension> (0);
    auto ext3 = std::make_shared <test_extension> (1);

    m.setExtension ("ext1", ext1);
    m.setExtension ("ext2", ext2);
    m.setExtension ("ext3", ext3);

    BOOST_CHECK_EQUAL (m.getExtension ("ext1"), ext1.get ());
    BOOST_CHECK_EQUAL (m.getExtension ("ext2"), ext2.get ());
    BOOST_CHECK_EQUAL (m.getExtension ("ext3"), ext3.get ());
}

BOOST_AUTO_TEST_SUITE_END ()
