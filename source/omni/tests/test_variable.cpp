#include <omni/core/variable_declaration_statement.hpp>
#include <omni/core/variable_expression.hpp>
#include <omni/core/variable_assignment_expression.hpp>
#include <omni/core/binary_operator_expression.hpp>
#include <omni/core/expression_statement.hpp>
#include <omni/core/context.hpp>
#include <omni/core/module.hpp>
#include <omni/core/function.hpp>
#include <omni/core/type.hpp>
#include <omni/core/block.hpp>
#include <omni/core/literal_expression.hpp>
#include <omni/core/builtin_literal.hpp>
#include <omni/core/return_statement.hpp>

#include <omni/tests/test_utils.hpp>

#include <boost/test/unit_test.hpp>

/**
Tests the classes variable_declaration_statement, variable_expressiond and variable_assignment_expression.
**/
BOOST_AUTO_TEST_SUITE (variableTests)

BOOST_AUTO_TEST_CASE (ctor)
{
    using namespace omni::core;
    context c;
    auto variable = std::make_shared <variable_declaration_statement> (c.sharedBasicType (type_class::t_char));
    variable_expression variableExpression (variable);
}

/**
Does some fiddling with variable_declaration_statement, variable_expression and variable_assignment_expression.
**/
BOOST_AUTO_TEST_CASE (mixedTests)
{
    using namespace omni::core;
    context c;
    module m (c, "test");
    auto t = c.sharedBasicType (type_class::t_char);
    auto body = std::make_shared <block> ();
    // Declare a variable "A" that holds the letter 'A':
    auto variableA = std::make_shared <variable_declaration_statement> (
        std::make_shared <literal_expression> (
            std::make_shared <builtin_literal <char>> (c, 'A')));
    body->appendStatement (variableA);
    // Declare a second variable "B" that holds the value of variableA, incremented by 1. Hence, the value should be 'B'
    auto AplusBexpression = std::make_shared <binary_operator_expression> (
        binary_operator_expression::binary_operation::binary_plus_operation,
        std::make_shared <variable_expression> (variableA),
        std::make_shared <literal_expression> (std::make_shared <builtin_literal<char>> (c, static_cast <char> (1))));
    auto variableB = std::make_shared <variable_declaration_statement> (AplusBexpression);
    body->appendStatement (variableB);
    // Declare a third variable C that will be initialized with the letter 'A', but then (without usage of the letter 'A') it will be assigned
    // the result of variableB plus 1. Hence, the value should be 'C'.
    auto variableC = std::make_shared <variable_declaration_statement> (std::make_shared <literal_expression> (std::make_shared <builtin_literal<char>> (c, 'A')));
    body->appendStatement (variableC);
    auto variableCassignment = std::make_shared <variable_assignment_expression> (
        variableC,
        std::make_shared <binary_operator_expression> (
            binary_operator_expression::binary_operation::binary_plus_operation,
            std::make_shared <variable_expression> (variableB),
            std::make_shared <literal_expression> (std::make_shared <builtin_literal<char>> (c, static_cast <char> (1)))));
    body->appendStatement (std::make_shared <expression_statement> (variableCassignment));

    // Now, return the value of variable "C", which should be 'C':
    body->appendStatement (std::make_shared <return_statement> (std::make_shared <variable_expression> (variableC)));

    auto func = std::make_shared <function> (m, "test", c.sharedBasicType (type_class::t_char), body);
    m.addFunction (func);

    omni::tests::test_file_manager testFileManager;
    char result = omni::tests::runFunction <char> (func, testFileManager, "variableMixedTests");
    BOOST_CHECK_EQUAL (result, 'C');
}


BOOST_AUTO_TEST_SUITE_END ();
