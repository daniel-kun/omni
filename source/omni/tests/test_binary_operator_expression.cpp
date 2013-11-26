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
#include <limits>

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

class test_binary_operator_expression_fixture {
public:
        test_binary_operator_expression_fixture () :
            _testCounter (0u),
            _context ()
        {
        }
protected:
    std::size_t _testCounter;
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
    T result = omni::tests::runFunction <T> (func, testFileManager, testFuncName);
    return result;
}

/**
We are using a macro here because the BOOST_CHECK_EQUAL will print out the original expressions for LEFT and RIGHT instead of just the results.
This offers a better orientation when a BOOST_CHECK_EQUAL failes.
**/
#define TEST_PLUS(TESTCOUNTER, CONTEXT, LEFT, RIGHT) { \
    auto result = test (TESTCOUNTER,\
                        CONTEXT,\
                        omni::take2::binary_operator_expression::binary_operation::binary_plus_operation,\
                        new omni::take2::builtin_literal <decltype(LEFT)> (CONTEXT, LEFT),\
                        new omni::take2::builtin_literal <decltype(RIGHT)> (CONTEXT, RIGHT));\
    BOOST_CHECK_EQUAL (result, static_cast <decltype (LEFT)> (LEFT + RIGHT));\
    if (result != static_cast <decltype (LEFT)> (LEFT + RIGHT)) { \
        std::stringstream fileName; \
        fileName << "binaryOperatorExpressionTest" << TESTCOUNTER << ".ll"; \
        omni::tests::test_file_manager testFileManager; \
        CONTEXT.emitAssemblyFile(testFileManager.getTestFileName (fileName.str (), false).string ()); \
    } \
}


template <typename T>
void testNumericLimits (std::size_t & testCounter, omni::take2::context & c)
{
    TEST_PLUS (testCounter, c, 0, 0);
    TEST_PLUS (testCounter, c, std::numeric_limits <T>::min (),     std::numeric_limits <T>::min ());
    TEST_PLUS (testCounter, c, std::numeric_limits <T>::max (),     std::numeric_limits <T>::max ());
    TEST_PLUS (testCounter, c, std::numeric_limits <T>::max () / 2, std::numeric_limits <T>::max () / 2);
}

BOOST_FIXTURE_TEST_SUITE (binaryOperatorExpressionTest, test_binary_operator_expression_fixture)

BOOST_AUTO_TEST_CASE (plusSignedShortNumericLimits)
{
    using namespace omni::take2;
    testNumericLimits <signed short> (_testCounter, _context);
}

BOOST_AUTO_TEST_CASE (plusSignedShort1)
{
    using namespace omni::take2;
    TEST_PLUS (_testCounter, _context, 1, 1);
}

BOOST_AUTO_TEST_CASE (plusSignedShort2)
{
    using namespace omni::take2;
    TEST_PLUS (_testCounter, _context, 256, 256);
}

BOOST_AUTO_TEST_CASE (plusSignedShort3)
{
    using namespace omni::take2;
    TEST_PLUS (_testCounter, _context, -1, -1);
}

BOOST_AUTO_TEST_CASE (plusSignedShort4)
{
    using namespace omni::take2;
    TEST_PLUS (_testCounter, _context, -256, -256);
}

BOOST_AUTO_TEST_CASE (plusUnsignedShortNumericLimits)
{
    using namespace omni::take2;
    testNumericLimits <unsigned short> (_testCounter, _context);
}

BOOST_AUTO_TEST_CASE (plusUnsignedShort1)
{
    using namespace omni::take2;
    TEST_PLUS (_testCounter, _context, 1, 1);
}

BOOST_AUTO_TEST_CASE (plusUnsignedShort2)
{
    using namespace omni::take2;
    TEST_PLUS (_testCounter, _context, 256, 256);
}

BOOST_AUTO_TEST_CASE (plusUnsignedShort3)
{
    using namespace omni::take2;
    TEST_PLUS (_testCounter, _context, 0, 1);
}

BOOST_AUTO_TEST_CASE (plusUnsignedShort4)
{
    using namespace omni::take2;
    TEST_PLUS (_testCounter, _context, 0, -256);
}

BOOST_AUTO_TEST_CASE (plusSignedInt)
{
    using namespace omni::take2;

    testNumericLimits <signed int> (_testCounter, _context);
    TEST_PLUS (_testCounter, _context, 1, 1);
    TEST_PLUS (_testCounter, _context, 256, 256);
    TEST_PLUS (_testCounter, _context, -1, -1);
    TEST_PLUS (_testCounter, _context, -256, -256);
}

BOOST_AUTO_TEST_CASE (plusUnsignedInt)
{
    using namespace omni::take2;
    testNumericLimits <unsigned int> (_testCounter, _context);
    TEST_PLUS (_testCounter, _context, 1u, 1u);
    TEST_PLUS (_testCounter, _context, 256u, 256u);
    TEST_PLUS (_testCounter, _context, (static_cast <unsigned int> (std::numeric_limits <signed int>::max ()) + 1u), 1u);
    TEST_PLUS (_testCounter, _context, (static_cast <unsigned int> (std::numeric_limits <signed int>::max ()) + 1u), (static_cast <unsigned int> (std::numeric_limits <signed int>::max ()) + 1u));
}

BOOST_AUTO_TEST_SUITE_END ();
