#include <omni/core/binary_operator_expression.hpp>
#include <omni/core/context.hpp>
#include <omni/core/module.hpp>
#include <omni/core/function.hpp>
#include <omni/core/block.hpp>
#include <omni/core/builtin_literal.hpp>
#include <omni/core/literal_expression.hpp>
#include <omni/core/expression_statement.hpp>

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
            _context (),
            _module (_context, "test")
        {
        }
protected:
    std::size_t _testCounter;
    omni::core::context _context;
    omni::core::module _module;
};

template <typename T>
T test (std::size_t & testCounter,
        omni::core::module & m,
        omni::core::binary_operator_expression::binary_operation operation,
        omni::core::builtin_literal <T> * left,
        omni::core::builtin_literal <T> * right)
{
    using namespace omni::core;
    std::shared_ptr <block> body (new block ());
    std::shared_ptr <literal_expression> leftExpression (new literal_expression (std::shared_ptr <literal> (left)));
    std::shared_ptr <literal_expression> rightExpression (new literal_expression (std::shared_ptr <literal> (right)));
    body->appendStatement (
        std::shared_ptr <statement> (
            new return_statement (
                std::shared_ptr <expression> (new binary_operator_expression (m.getContext (), operation, leftExpression, rightExpression)))));
    std::stringstream funcName;
    funcName << "binaryOperatorExpressionTest" << ++ testCounter;
    std::string testFuncName = funcName.str ();
    std::shared_ptr <function> func (new function (m, testFuncName, left->getType (), body));
    m.addFunction (func);
    omni::tests::test_file_manager testFileManager;
    T result = omni::tests::runFunction <T> (func, testFileManager, testFuncName);
    return result;
}

/**
We are using a macro here because the BOOST_CHECK_EQUAL will print out the original expressions for LEFT and RIGHT instead of just the results.
This offers a better orientation when a BOOST_CHECK_EQUAL failes.
**/
#define TEST_BINOP(TESTCOUNTER, MODULE, OPERATION, OPERATOR, LEFT, RIGHT) { \
    auto result = test (TESTCOUNTER,\
                        MODULE,\
                        OPERATION,\
                        new omni::core::builtin_literal <decltype(LEFT)> (MODULE.getContext (), LEFT),\
                        new omni::core::builtin_literal <decltype(RIGHT)> (MODULE.getContext (), RIGHT));\
    BOOST_CHECK_EQUAL (result, static_cast <decltype (LEFT)> (LEFT OPERATOR RIGHT));\
    if (result != static_cast <decltype (LEFT)> (LEFT OPERATOR RIGHT)) { \
        std::stringstream fileName; \
        fileName << "binaryOperatorExpressionTest" << TESTCOUNTER << ".ll"; \
        omni::tests::test_file_manager testFileManager; \
        MODULE.emitAssemblyFile(testFileManager.getTestFileName (fileName.str (), false).string ()); \
    } \
}

/////////// PLUS //////////

#define TEST_PLUS(TESTCOUNTER, MODULE, LEFT, RIGHT) TEST_BINOP(TESTCOUNTER, MODULE, omni::core::binary_operator_expression::binary_operation::binary_plus_operation, +, LEFT, RIGHT)

template <typename T>
void testNumericLimitsPlus (std::size_t & testCounter, omni::core::module & mod)
{
    TEST_BINOP (testCounter, mod, omni::core::binary_operator_expression::binary_operation::binary_plus_operation, +, 0, 0);
    TEST_BINOP (testCounter, mod, omni::core::binary_operator_expression::binary_operation::binary_plus_operation, +, std::numeric_limits <T>::min (),     std::numeric_limits <T>::min ());
    TEST_BINOP (testCounter, mod, omni::core::binary_operator_expression::binary_operation::binary_plus_operation, +, std::numeric_limits <T>::max (),     std::numeric_limits <T>::max ());
    TEST_BINOP (testCounter, mod, omni::core::binary_operator_expression::binary_operation::binary_plus_operation, +, std::numeric_limits <T>::max () / 2, std::numeric_limits <T>::max () / 2);
}

BOOST_FIXTURE_TEST_SUITE (binaryOperatorExpressionTest, test_binary_operator_expression_fixture)

BOOST_AUTO_TEST_CASE (plusSignedShortNumericLimits)
{
    using namespace omni::core;
    testNumericLimitsPlus <signed short> (_testCounter, _module);
}

BOOST_AUTO_TEST_CASE (plusSignedShort1)
{
    using namespace omni::core;
    TEST_PLUS (_testCounter, _module, 1, 1);
}

BOOST_AUTO_TEST_CASE (plusSignedShort2)
{
    using namespace omni::core;
    TEST_PLUS (_testCounter, _module, 256, 256);
}

BOOST_AUTO_TEST_CASE (plusSignedShort3)
{
    using namespace omni::core;
    TEST_PLUS (_testCounter, _module, -1, -1);
}

BOOST_AUTO_TEST_CASE (plusSignedShort4)
{
    using namespace omni::core;
    TEST_PLUS (_testCounter, _module, -256, -256);
}

BOOST_AUTO_TEST_CASE (plusUnsignedShortNumericLimits)
{
    using namespace omni::core;
    testNumericLimitsPlus <unsigned short> (_testCounter, _module);
}

BOOST_AUTO_TEST_CASE (plusUnsignedShort1)
{
    using namespace omni::core;
    TEST_PLUS (_testCounter, _module, 1, 1);
}

BOOST_AUTO_TEST_CASE (plusUnsignedShort2)
{
    using namespace omni::core;
    TEST_PLUS (_testCounter, _module, 256, 256);
}

BOOST_AUTO_TEST_CASE (plusUnsignedShort3)
{
    using namespace omni::core;
    TEST_PLUS (_testCounter, _module, 0, 1);
}

BOOST_AUTO_TEST_CASE (plusUnsignedShort4)
{
    using namespace omni::core;
    TEST_PLUS (_testCounter, _module, 0, -256);
}

BOOST_AUTO_TEST_CASE (plusSignedInt)
{
    using namespace omni::core;

    testNumericLimitsPlus <signed int> (_testCounter, _module);
    TEST_PLUS (_testCounter, _module, 1, 1);
    TEST_PLUS (_testCounter, _module, 256, 256);
    TEST_PLUS (_testCounter, _module, -1, -1);
    TEST_PLUS (_testCounter, _module, -256, -256);
}

BOOST_AUTO_TEST_CASE (plusUnsignedInt)
{
    using namespace omni::core;
    testNumericLimitsPlus <unsigned int> (_testCounter, _module);
    TEST_PLUS (_testCounter, _module, 1u, 1u);
    TEST_PLUS (_testCounter, _module, 256u, 256u);
    TEST_PLUS (_testCounter, _module, (static_cast <unsigned int> (std::numeric_limits <signed int>::max ()) + 1u), 1u);
    TEST_PLUS (_testCounter, _module, (static_cast <unsigned int> (std::numeric_limits <signed int>::max ()) + 1u), (static_cast <unsigned int> (std::numeric_limits <signed int>::max ()) + 1u));
}

/////////// MINUS //////////

#define TEST_MINUS(TESTCOUNTER, MODULE, LEFT, RIGHT) TEST_BINOP(TESTCOUNTER, MODULE, omni::core::binary_operator_expression::binary_operation::binary_minus_operation, -, LEFT, RIGHT)

template <typename T>
void testNumericLimitsMinus (std::size_t & testCounter, omni::core::module & m)
{
    TEST_BINOP (testCounter, m, omni::core::binary_operator_expression::binary_operation::binary_minus_operation, -, 0, 0);
    TEST_BINOP (testCounter, m, omni::core::binary_operator_expression::binary_operation::binary_minus_operation, -, std::numeric_limits <T>::min (),     std::numeric_limits <T>::min ());
    TEST_BINOP (testCounter, m, omni::core::binary_operator_expression::binary_operation::binary_minus_operation, -, std::numeric_limits <T>::max (),     std::numeric_limits <T>::max ());
    TEST_BINOP (testCounter, m, omni::core::binary_operator_expression::binary_operation::binary_minus_operation, -, std::numeric_limits <T>::max () / 2, std::numeric_limits <T>::max () / 2);
}

BOOST_AUTO_TEST_CASE (minusSignedShortNumericLimits)
{
    using namespace omni::core;
    testNumericLimitsMinus <signed short> (_testCounter, _module);
}

BOOST_AUTO_TEST_CASE (minusSignedShort1)
{
    using namespace omni::core;
    TEST_MINUS (_testCounter, _module, 1, 1);
}

BOOST_AUTO_TEST_CASE (minusSignedShort2)
{
    using namespace omni::core;
    TEST_MINUS (_testCounter, _module, 256, 256);
}

BOOST_AUTO_TEST_CASE (minusSignedShort3)
{
    using namespace omni::core;
    TEST_MINUS (_testCounter, _module, -1, -1);
}

BOOST_AUTO_TEST_CASE (minusSignedShort4)
{
    using namespace omni::core;
    TEST_MINUS (_testCounter, _module, -256, -256);
}

BOOST_AUTO_TEST_CASE (minusUnsignedShortNumericLimits)
{
    using namespace omni::core;
    testNumericLimitsMinus <unsigned short> (_testCounter, _module);
}

BOOST_AUTO_TEST_CASE (minusUnsignedShort1)
{
    using namespace omni::core;
    TEST_MINUS (_testCounter, _module, 1, 1);
}

BOOST_AUTO_TEST_CASE (minusUnsignedShort2)
{
    using namespace omni::core;
    TEST_MINUS (_testCounter, _module, 256, 256);
}

BOOST_AUTO_TEST_CASE (minusUnsignedShort3)
{
    using namespace omni::core;
    TEST_MINUS (_testCounter, _module, 0, 1);
}

BOOST_AUTO_TEST_CASE (minusUnsignedShort4)
{
    using namespace omni::core;
    TEST_MINUS (_testCounter, _module, 0, -256);
}

BOOST_AUTO_TEST_CASE (minusSignedInt)
{
    using namespace omni::core;

    testNumericLimitsMinus <signed int> (_testCounter, _module);
    TEST_MINUS (_testCounter, _module, 1, 1);
    TEST_MINUS (_testCounter, _module, 256, 256);
    TEST_MINUS (_testCounter, _module, -1, -1);
    TEST_MINUS (_testCounter, _module, -256, -256);
}

BOOST_AUTO_TEST_CASE (minusUnsignedInt)
{
    using namespace omni::core;
    testNumericLimitsMinus <unsigned int> (_testCounter, _module);
    TEST_MINUS (_testCounter, _module, 1u, 1u);
    TEST_MINUS (_testCounter, _module, 256u, 256u);
    TEST_MINUS (_testCounter, _module, (static_cast <unsigned int> (std::numeric_limits <signed int>::max ()) + 1u), 1u);
    TEST_MINUS (_testCounter, _module, (static_cast <unsigned int> (std::numeric_limits <signed int>::max ()) + 1u), (static_cast <unsigned int> (std::numeric_limits <signed int>::max ()) + 1u));
}

BOOST_AUTO_TEST_SUITE_END ();
