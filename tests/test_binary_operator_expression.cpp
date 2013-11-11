#include <omni/take2/binary_operator_expression.hpp>
#include <omni/take2/context.hpp>
#include <omni/take2/function.hpp>
#include <omni/take2/block.hpp>
#include <omni/take2/builtin_literal.hpp>
#include <omni/take2/literal_expression.hpp>
#include <omni/take2/expression_statement.hpp>

#include <omni/tests/test_utils.hpp>
#include <omni/tests/test_file_manager.hpp>

#include <boost/test/unit_test.hpp>

#include <sstream>

class test_binary_operator_expression_fixture {
public:
protected:
    omni::take2::context _context;
};

template <typename T>
T test (std::size_t & testCounter,
        omni::take2::context & c,
        omni::take2::binary_operator_expression::binary_operation operation,
        omni::take2::builtin_literal <T> * left,
        omni::take2::builtin_literal <T> * right)
{
    using namespace omni::take2;
    std::shared_ptr <block> body (new block ());
    std::shared_ptr <literal_expression> leftExpression (new literal_expression (std::shared_ptr <literal> (left)));
    std::shared_ptr <literal_expression> rightExpression (new literal_expression (std::shared_ptr <literal> (right)));
    body->appendStatement (
        std::shared_ptr <statement> (
            new return_statement (
                std::shared_ptr <expression> (new binary_operator_expression (operation, leftExpression, rightExpression)))));
    std::stringstream funcName;
    funcName << "binaryOperatorExpressionTest" << ++ testCounter;
    std::string testFuncName = funcName.str ();
    std::shared_ptr <function> func (new function (testFuncName, left->getType (), body));
    c.addFunction (func);
    omni::tests::test_file_manager testFileManager;
    return omni::tests::runFunction <T> (func, testFileManager, testFuncName);
}

BOOST_FIXTURE_TEST_SUITE (binaryOperatorExpressionTest, test_binary_operator_expression_fixture)

BOOST_AUTO_TEST_CASE (plusSignedInt)
{
    using namespace omni::take2;
    std::size_t testCounter = 0;
    test (testCounter,
          _context,
          binary_operator_expression::binary_operation::binary_plus_operation,
          new builtin_literal <int> (_context, 0),
          new builtin_literal <int> (_context, 0));

    test (testCounter,
          _context,
          binary_operator_expression::binary_operation::binary_plus_operation,
          new builtin_literal <int> (_context, 0),
          new builtin_literal <int> (_context, 0));
}

BOOST_AUTO_TEST_SUITE_END ();
