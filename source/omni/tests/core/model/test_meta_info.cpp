#include <omni/core/model/meta_info.hpp>
#include <omni/core/model/entity.hpp>
#include <omni/core/model/type.hpp>
#include <omni/core/model/scope.hpp>
#include <omni/core/model/function_prototype.hpp>
#include <omni/core/model/external_function.hpp>
#include <omni/core/model/function.hpp>
#include <omni/core/model/module.hpp>
#include <omni/core/model/parameter.hpp>
#include <omni/core/model/statement.hpp>
#include <omni/core/model/block.hpp>
#include <omni/core/model/expression.hpp>
#include <omni/core/model/modifying_expression.hpp>
#include <omni/core/model/function_call_expression.hpp>
#include <omni/core/model/variable_assignment_expression.hpp>
#include <omni/core/model/pure_expression.hpp>
#include <omni/core/model/binary_operator_expression.hpp>
#include <omni/core/model/cast_expression.hpp>
#include <omni/core/model/bitcast_expression.hpp>
#include <omni/core/model/literal_expression.hpp>
#include <omni/core/model/builtin_literal_expression.hpp>
#include <omni/core/model/variable_declaration_expression.hpp>
#include <omni/core/model/variable_expression.hpp>
#include <omni/core/model/if_statement.hpp>
#include <omni/core/model/return_statement.hpp>
#include <omni/core/model/while_statement.hpp>
#include <omni/core/model/do_while_statement.hpp>

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

BOOST_AUTO_TEST_CASE (staticInit)
{
#define OMNI_TEST_CHECK_META_INFO_NAME(A) \
    BOOST_CHECK_EQUAL (omni::core::model::A::getStaticMetaInfo ().getName (), #A);
    OMNI_TEST_CHECK_META_INFO_NAME (entity);
    OMNI_TEST_CHECK_META_INFO_NAME (type);
    OMNI_TEST_CHECK_META_INFO_NAME (scope);
    OMNI_TEST_CHECK_META_INFO_NAME (function_prototype);
    OMNI_TEST_CHECK_META_INFO_NAME (external_function);
    OMNI_TEST_CHECK_META_INFO_NAME (function);
    OMNI_TEST_CHECK_META_INFO_NAME (module);
    OMNI_TEST_CHECK_META_INFO_NAME (parameter);
    OMNI_TEST_CHECK_META_INFO_NAME (statement);
    OMNI_TEST_CHECK_META_INFO_NAME (block);
    OMNI_TEST_CHECK_META_INFO_NAME (expression);
    OMNI_TEST_CHECK_META_INFO_NAME (modifying_expression);
    OMNI_TEST_CHECK_META_INFO_NAME (function_call_expression);
    OMNI_TEST_CHECK_META_INFO_NAME (variable_assignment_expression);
    OMNI_TEST_CHECK_META_INFO_NAME (pure_expression);
    OMNI_TEST_CHECK_META_INFO_NAME (binary_operator_expression);
    OMNI_TEST_CHECK_META_INFO_NAME (cast_expression);
    OMNI_TEST_CHECK_META_INFO_NAME (bitcast_expression);
    OMNI_TEST_CHECK_META_INFO_NAME (literal_expression);
    OMNI_TEST_CHECK_META_INFO_NAME (variable_declaration_expression);
    OMNI_TEST_CHECK_META_INFO_NAME (variable_expression);
    OMNI_TEST_CHECK_META_INFO_NAME (if_statement);
    OMNI_TEST_CHECK_META_INFO_NAME (return_statement);
    OMNI_TEST_CHECK_META_INFO_NAME (while_statement);
    OMNI_TEST_CHECK_META_INFO_NAME (do_while_statement);
#undef OMNI_TEST_CHECK_META_INFO_NAME
    BOOST_CHECK_EQUAL (omni::core::model::builtin_literal_expression<int>::getStaticMetaInfo ().getName (), "builtin_literal_expression");
}

BOOST_AUTO_TEST_SUITE_END ()
