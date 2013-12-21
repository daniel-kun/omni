#include <omni/core/while_statement.hpp>
#include <omni/core/context.hpp>
#include <omni/core/module.hpp>
#include <omni/core/function.hpp>
#include <omni/core/block.hpp>
#include <omni/core/literal_expression.hpp>
#include <omni/core/expression_statement.hpp>
#include <omni/core/builtin_literal.hpp>
#include <omni/core/return_statement.hpp>
#include <omni/core/variable_declaration_statement.hpp>
#include <omni/core/variable_assignment_expression.hpp>
#include <omni/core/variable_expression.hpp>
#include <omni/core/binary_operator_expression.hpp>

#include <omni/tests/test_file_manager.hpp>
#include <omni/tests/test_utils.hpp>

#include <boost/test/auto_unit_test.hpp>

BOOST_AUTO_TEST_SUITE (whileStatementTests)

BOOST_AUTO_TEST_CASE (ctor)
{
    using namespace omni::core;
    context c;
    module m (c, "test");

    while_statement whileStatement (std::make_shared <literal_expression> (std::make_shared <builtin_literal <bool>> (c, true)), std::make_shared <block> ());
}

BOOST_AUTO_TEST_CASE (mixedTests)
{
    using namespace omni::core;
    context c;
    module m (c, "test");

    auto body = std::make_shared <block> ();
    auto variableDeclaration = std::make_shared <variable_declaration_statement> (std::make_shared <literal_expression> (std::make_shared <builtin_literal <int>> (c, 1)));
    body->appendStatement (variableDeclaration);

    auto whileCondition = std::make_shared <binary_operator_expression> (
        c,
        binary_operator_expression::binary_operation::binary_lessthan_operation,
        std::make_shared <variable_expression> (variableDeclaration),
        std::make_shared <literal_expression> (
            std::make_shared <builtin_literal<int>> (c, 10)));

    auto whileBody = std::make_shared <block> ();
    whileBody->appendStatement (
        std::make_shared <expression_statement> (
            std::make_shared <variable_assignment_expression> (
                variableDeclaration,
                std::make_shared <binary_operator_expression> (
                    c,
                    binary_operator_expression::binary_operation::binary_plus_operation,
                    std::make_shared <variable_expression> (variableDeclaration),
                    std::make_shared <literal_expression> (
                        std::make_shared <builtin_literal <int>> (c, 1))))));
    auto whileStatement = std::make_shared <while_statement> (whileCondition, whileBody);
    body->appendStatement (whileStatement);
    body->appendStatement (std::make_shared <return_statement> (std::make_shared <variable_expression> (variableDeclaration)));

    auto func = m.createFunction ("test", variableDeclaration->getVariableType (), body);

    omni::tests::test_file_manager testFileManager;
    int result = omni::tests::runFunction <int> (func, testFileManager, "whileStatementTest");
    BOOST_CHECK_EQUAL (result, 10);
}

BOOST_AUTO_TEST_SUITE_END ()
