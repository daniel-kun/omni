#include <omni/core/variable_declaration_expression.hpp>
#include <omni/core/variable_expression.hpp>
#include <omni/core/variable_assignment_expression.hpp>
#include <omni/core/binary_operator_expression.hpp>
#include <omni/core/context.hpp>
#include <omni/core/module.hpp>
#include <omni/core/function.hpp>
#include <omni/core/type.hpp>
#include <omni/core/type_class.hpp>
#include <omni/core/block.hpp>
#include <omni/core/literal_expression.hpp>
#include <omni/core/builtin_literal.hpp>
#include <omni/core/return_statement.hpp>

#include <omni/tests/test_utils.hpp>

#include <boost/test/unit_test.hpp>

#include <numeric>

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

namespace {
template <typename T>
void testVariables (T initializationValue, T assignmentValue)
{
    BOOST_CHECK_NE (initializationValue, assignmentValue);
    using namespace omni::core;
    context c;
    module m (c, "test");
    
    // Declare a variable with the initial value of `initializationValue':
    auto variableInitializationLiteral = std::make_shared <builtin_literal<T>> (c, initializationValue);
    auto variableInitializationExpression = std::make_shared <literal_expression> (variableInitializationLiteral);
    auto variableDeclarationStatement = std::make_shared <variable_declaration_expression> (variableInitializationExpression);
    BOOST_CHECK (variableDeclarationStatement->getType ()->getTypeClass () == native_type_to_type_class <T>::typeClass);

    // Assign `assignmentValue' to the variable:
    auto variableValueLiteral = std::make_shared <builtin_literal<T>> (c, assignmentValue);
    auto variableValueExpression = std::make_shared <literal_expression> (variableValueLiteral);
    auto variableAssignmentExpression = std::make_shared <variable_assignment_expression> (variableDeclarationStatement, variableValueExpression);

    // Add the statements to a function body:
    auto body = std::make_shared <block> ();
    body->appendStatement (variableDeclarationStatement);
    body->appendStatement (variableAssignmentExpression);

    // Return the variable's value:
    body->appendStatement (
        std::make_shared <return_statement> (
            std::make_shared <variable_expression> (variableDeclarationStatement)));
    
    auto func = m.createFunction ("test", variableDeclarationStatement->getType (), body);

    omni::tests::test_file_manager testFileManager;
    T result = omni::tests::runFunction <T> (func, testFileManager, "variableTest");
    BOOST_CHECK_EQUAL (result, assignmentValue);
}

template <typename T>
void testVariablesNumericLimits ()
{
    testVariables <T> (std::numeric_limits <T>::max (), std::numeric_limits <T>::min ());
    testVariables <T> (std::numeric_limits <T>::min (), std::numeric_limits <T>::max ());
}
} // anonymous namespace

/**
Tests the classes variable_declaration_expression, variable_expression and variable_assignment_expression.
**/
BOOST_AUTO_TEST_SUITE (variableTests)

BOOST_AUTO_TEST_CASE (ctor)
{
    using namespace omni::core;
    context c;
    auto variable = std::make_shared <variable_declaration_expression> (c.sharedBasicType (type_class::t_char));
    variable_expression variableExpression (variable);
}

/**
Does some fiddling with variable_declaration_expression, variable_expression and variable_assignment_expression.
**/
BOOST_AUTO_TEST_CASE (mixedTests)
{
    using namespace omni::core;
    context c;
    module m (c, "test");
    auto t = c.sharedBasicType (type_class::t_char);
    auto body = std::make_shared <block> ();
    // Declare a variable "A" that holds the letter 'A':
    auto variableA = std::make_shared <variable_declaration_expression> (
        std::make_shared <literal_expression> (
            std::make_shared <builtin_literal <char>> (c, 'A')));
    body->appendStatement (variableA);
    // Declare a second variable "B" that holds the value of variableA, incremented by 1. Hence, the value should be 'B'
    auto AplusBexpression = std::make_shared <binary_operator_expression> (
        c,
        binary_operator_expression::binary_operation::binary_plus_operation,
        std::make_shared <variable_expression> (variableA),
        std::make_shared <literal_expression> (std::make_shared <builtin_literal<char>> (c, static_cast <char> (1))));
    auto variableB = std::make_shared <variable_declaration_expression> (AplusBexpression);
    body->appendStatement (variableB);
    // Declare a third variable C that will be initialized with the letter 'A', but then (without usage of the letter 'A') it will be assigned
    // the result of variableB plus 1. Hence, the value should be 'C'.
    auto variableC = std::make_shared <variable_declaration_expression> (std::make_shared <literal_expression> (std::make_shared <builtin_literal<char>> (c, 'A')));
    body->appendStatement (variableC);
    auto variableCassignment = std::make_shared <variable_assignment_expression> (
        variableC,
        std::make_shared <binary_operator_expression> (
            c,
            binary_operator_expression::binary_operation::binary_plus_operation,
            std::make_shared <variable_expression> (variableB),
            std::make_shared <literal_expression> (std::make_shared <builtin_literal<char>> (c, static_cast <char> (1)))));
    body->appendStatement (variableCassignment);

    // Now, return the value of variable "C", which should be 'C':
    body->appendStatement (std::make_shared <return_statement> (std::make_shared <variable_expression> (variableC)));

    auto func = std::make_shared <function> (m, "test", c.sharedBasicType (type_class::t_char), body);
    m.addFunction (func);

    omni::tests::test_file_manager testFileManager;
    char result = omni::tests::runFunction <char> (func, testFileManager, "variableMixedTests");
    BOOST_CHECK_EQUAL (result, 'C');
}

BOOST_AUTO_TEST_CASE (variableBoolean)
{
    testVariables <bool> (true, false);
    testVariables <bool> (false, true);
    testVariablesNumericLimits <bool> ();
}

BOOST_AUTO_TEST_CASE (variableChar)
{
    testVariables <char> ('A', 'B');
    testVariables <char> ('A', '\0');
    testVariablesNumericLimits <char> ();
}

BOOST_AUTO_TEST_CASE (variableUnsignedByte)
{
    testVariables <unsigned char> ('A', 'B');
    testVariables <unsigned char> ('A', '\0');
    testVariablesNumericLimits <unsigned char> ();
}

BOOST_AUTO_TEST_CASE (variableSignedByte)
{
    testVariables <signed char> (-1, 0);
    testVariables <signed char> (+1, 0);
    testVariables <signed char> (0, -1);
    testVariables <signed char> (0, +1);
    testVariablesNumericLimits <signed char> ();
}

BOOST_AUTO_TEST_CASE (variableUnsignedShort)
{
    testVariables <unsigned short> (1, 0);
    testVariables <unsigned short> (0, 1);
    testVariablesNumericLimits <unsigned short> ();
}

BOOST_AUTO_TEST_CASE (variableSignedShort)
{
    testVariables <signed short> (-1, 0);
    testVariables <signed short> (+1, 0);
    testVariables <signed short> (0, -1);
    testVariables <signed short> (0, +1);
    testVariablesNumericLimits <signed short> ();
}

BOOST_AUTO_TEST_CASE (variableUnsignedInt)
{
    testVariables <unsigned int> (1, 0);
    testVariables <unsigned int> (0, 1);
    testVariablesNumericLimits <unsigned int> ();
}

BOOST_AUTO_TEST_CASE (variableSignedInt)
{
    testVariables <signed int> (-1, 0);
    testVariables <signed int> (+1, 0);
    testVariables <signed int> (0, -1);
    testVariables <signed int> (0, +1);
    testVariablesNumericLimits <signed int> ();
}

BOOST_AUTO_TEST_CASE (variableUnsignedLong)
{
    testVariables <unsigned long> (1, 0);
    testVariables <unsigned long> (0, 1);
    testVariablesNumericLimits <unsigned long> ();
}

BOOST_AUTO_TEST_CASE (variableSignedLong)
{
    testVariables <signed long> (-1, 0);
    testVariables <signed long> (+1, 0);
    testVariables <signed long> (0, -1);
    testVariables <signed long> (0, +1);
    testVariablesNumericLimits <signed long> ();
}

BOOST_AUTO_TEST_CASE (variableUnsignedLongLong)
{
    testVariables <unsigned long long> (1, 0);
    testVariables <unsigned long long> (0, 1);
    testVariablesNumericLimits <unsigned long long> ();
}

BOOST_AUTO_TEST_CASE (variableSignedLongLong)
{
    testVariables <signed long long> (-1, 0);
    testVariables <signed long long> (+1, 0);
    testVariables <signed long long> (0, -1);
    testVariables <signed long long> (0, +1);
    testVariablesNumericLimits <signed long long> ();
}

BOOST_AUTO_TEST_SUITE_END ();
