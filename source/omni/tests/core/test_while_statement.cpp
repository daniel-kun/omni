#include <omni/core/while_statement.hpp>
#include <omni/core/do_while_statement.hpp>
#include <omni/core/context.hpp>
#include <omni/core/module.hpp>
#include <omni/core/function.hpp>
#include <omni/core/block.hpp>
#include <omni/core/literal_expression.hpp>
#include <omni/core/builtin_literal.hpp>
#include <omni/core/return_statement.hpp>
#include <omni/core/variable_declaration_expression.hpp>
#include <omni/core/variable_assignment_expression.hpp>
#include <omni/core/variable_expression.hpp>
#include <omni/core/binary_operator_expression.hpp>

#include <omni/tests/test_file_manager.hpp>
#include <omni/tests/test_utils.hpp>

#include <boost/test/auto_unit_test.hpp>

namespace {

/**
Builds and runs a example program that increments a variable that has been initialized with 1 with the exit-condition "variable < 10".
**/
template <typename WhileStatement>
int buildAndRunWhileTest (std::string testFileName)
{
    using namespace omni::core;
    context c;
    module m (c, "test");

    auto body = std::make_shared <model::block> ();
    auto variableDeclaration = std::make_shared <model::variable_declaration_expression> (std::make_shared <model::literal_expression> (std::make_shared <model::builtin_literal <int>> (c, 1)));
    body->appendStatement (variableDeclaration);

    auto whileCondition = std::make_shared <model::binary_operator_expression> (
        c,
        model::binary_operator_expression::binary_operation::binary_lessthan_operation,
        std::make_shared <model::variable_expression> (variableDeclaration),
        std::make_shared <model::literal_expression> (
            std::make_shared <model::builtin_literal <int>> (c, 10)));

    auto whileBody = std::make_shared <model::block> ();
    whileBody->appendStatement (
        std::make_shared <model::variable_assignment_expression> (
            variableDeclaration,
            std::make_shared <model::binary_operator_expression> (
                c,
                model::binary_operator_expression::binary_operation::binary_plus_operation,
                std::make_shared <model::variable_expression> (variableDeclaration),
                std::make_shared <model::literal_expression> (
                    std::make_shared <model::builtin_literal <int>> (c, 1)))));
    auto whileStatement = std::make_shared <WhileStatement> (whileCondition, whileBody);
    body->appendStatement (whileStatement);
    body->appendStatement (std::make_shared <model::return_statement> (std::make_shared <model::variable_expression> (variableDeclaration)));

    auto func = m.createFunction (testFileName, variableDeclaration->getType (), body);

    omni::tests::test_file_manager testFileManager;
    return omni::tests::runFunction <int> (func, testFileManager, testFileName);
}
}

/**
Tests the while_statement and do_while_statement.
**/
BOOST_AUTO_TEST_SUITE (whileStatementTests)

BOOST_AUTO_TEST_CASE (ctor)
{
    using namespace omni::core;
    context c;
    module m (c, "test");

    model::while_statement whileStatement (std::make_shared <model::literal_expression> (std::make_shared <model::builtin_literal <bool>> (c, true)), std::make_shared <model::block> ());
}

BOOST_AUTO_TEST_CASE (whileStatement)
{
    int result = buildAndRunWhileTest <omni::core::model::while_statement> ("whileStatementTest");
    BOOST_CHECK_EQUAL (result, 10);
}

/*
// TODO: This test creates a broken COFF obj file:
// See the test llvmTests/llvmPlaygroundDoWhile for a trimmed-down, baremetal version.
// See http://llvm.org/bugs/show_bug.cgi?id=18308

BOOST_AUTO_TEST_CASE (doWhileStatement)
{
    int result = buildAndRunWhileTest <omni::core::do_while_statement> ("doWhileStatementTest");
    BOOST_CHECK_EQUAL (result, 10);
}
*/

BOOST_AUTO_TEST_SUITE_END ()
