#include <omni/core/if_statement.hpp>
#include <omni/core/context.hpp>
#include <omni/core/module.hpp>
#include <omni/core/literal_expression.hpp>
#include <omni/core/builtin_literal.hpp>
#include <omni/core/return_statement.hpp>
#include <omni/core/block.hpp>
#include <omni/core/function.hpp>

#include <omni/tests/test_file_manager.hpp>
#include <omni/tests/test_utils.hpp>

#include <boost/test/auto_unit_test.hpp>

#include <sstream>

BOOST_AUTO_TEST_SUITE (ifStatementTests)

BOOST_AUTO_TEST_CASE (ctor)
{
    using namespace omni::core;
    context c;

    auto condition = std::make_shared <literal_expression> (std::make_shared <builtin_literal <bool>> (c, true));
    auto trueBlock = std::make_shared <block> ();
    auto elseBlock = std::make_shared <block> ();

    if_statement ifStatement (condition, trueBlock, elseBlock);
    BOOST_CHECK (ifStatement.getCondition () == condition);
    BOOST_CHECK (ifStatement.getTrueBlock () == trueBlock);
    BOOST_CHECK (ifStatement.getElseBlock () == elseBlock);

    if_statement ifStatement2 (condition, trueBlock, nullptr);
    BOOST_CHECK (ifStatement2.getCondition () == condition);
    BOOST_CHECK (ifStatement2.getTrueBlock () == trueBlock);
    BOOST_CHECK (ifStatement2.getElseBlock () == nullptr);
}

BOOST_AUTO_TEST_CASE (mixedTests)
{
    using namespace omni::core;
    context c;
    module m (c, "test");

    auto runDemo = [& c, & m] (bool cond) -> int 
    {
        auto condition = std::make_shared <literal_expression> (std::make_shared <builtin_literal <bool>> (c, cond));
        auto trueBlock = std::make_shared <block> ();
        trueBlock->appendStatement (std::make_shared <return_statement> (std::make_shared <literal_expression> (std::make_shared <builtin_literal <int>> (c, 42))));
        auto elseBlock = std::make_shared <block> ();
        elseBlock->appendStatement (std::make_shared <return_statement> (std::make_shared <literal_expression> (std::make_shared <builtin_literal <int>> (c, 128))));

        auto ifStatement = std::make_shared <if_statement> (condition, trueBlock, elseBlock);

        auto body = std::make_shared <block> ();
        body->appendStatement (ifStatement);

        std::stringstream str;
        str << "test" << cond;
        std::shared_ptr <function> func = m.createFunction (str.str (), c.sharedBasicType (type_class::t_signedInt), body);

        omni::tests::test_file_manager testFileManager;
        return omni::tests::runFunction <int> (func, testFileManager, "ifStatementMixedTests");
    };

    int result = runDemo (true);
    BOOST_CHECK_EQUAL (result, 42);
    BOOST_CHECK_NE (result, 128);
    
    result = runDemo (false);
    BOOST_CHECK_EQUAL (result, 128);
    BOOST_CHECK_NE (result, 42);
}

BOOST_AUTO_TEST_SUITE_END ()
