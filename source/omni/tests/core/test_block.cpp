#include <omni/core/model/block.hpp>
#include <omni/core/context.hpp>
#include <omni/core/module.hpp>
#include <omni/core/model/variable_declaration_expression.hpp>
#include <omni/core/model/variable_expression.hpp>
#include <omni/core/model/function.hpp>
#include <omni/core/model/return_statement.hpp>

#include <boost/test/auto_unit_test.hpp>

#include <functional>
#include <algorithm>

namespace {

typedef std::function <void (omni::core::model::block &,
                             std::shared_ptr <omni::core::model::variable_declaration_expression>,
                             std::shared_ptr <omni::core::model::expression>)> buildModuleBody;

/**
Builds a valid or an invalid module.
@param shouldBeValid True, if buildModule should build a valid module. False, if it should build an invalid module.
**/
void buildModule (bool shouldBeValid, buildModuleBody builder)
{
    using namespace omni::core;
    context c;
    module m (c, "test");

    auto t = c.sharedBasicType (model::type_class::t_signedInt);
    auto variableDeclaration = std::make_shared <model::variable_declaration_expression> (t);
    auto variableExpression = std::make_shared <model::variable_expression> (variableDeclaration);

    auto body = std::make_shared <model::block> ();
    builder (* body, variableDeclaration, variableExpression);
    body->appendStatement (std::make_shared <model::return_statement> (variableExpression));
    auto func = m.createFunction ("test", t, body);
    std::string errorInfo;
    bool isValid = m.verify (errorInfo);

    BOOST_CHECK_EQUAL (isValid, shouldBeValid);
    if (shouldBeValid) {
        BOOST_CHECK_EQUAL (errorInfo.length (), 0u);
    } else {
        BOOST_CHECK_NE (errorInfo.length (), 0u);
    }
}
}

BOOST_AUTO_TEST_SUITE (blockTests)

BOOST_AUTO_TEST_CASE (appendStatement)
{
    buildModule (true,
                 [] (omni::core::model::block & b,
                     std::shared_ptr <omni::core::model::variable_declaration_expression> decl,
                     std::shared_ptr <omni::core::model::expression> expr) -> void {
        b.appendStatement (decl);
        b.appendStatement (expr);
    });
    buildModule (false,
                 [] (omni::core::model::block & b,
                     std::shared_ptr <omni::core::model::variable_declaration_expression> decl,
                     std::shared_ptr <omni::core::model::expression> expr) -> void {
        b.appendStatement (expr);
        b.appendStatement (decl);
    });
}

BOOST_AUTO_TEST_CASE (prependStatement)
{
    buildModule (true,
                 [] (omni::core::model::block & b,
                     std::shared_ptr <omni::core::model::variable_declaration_expression> decl,
                     std::shared_ptr <omni::core::model::expression> expr) -> void {
        b.appendStatement (expr);
        b.prependStatement (decl);
    });
    buildModule (false,
                 [] (omni::core::model::block & b,
                     std::shared_ptr <omni::core::model::variable_declaration_expression> decl,
                     std::shared_ptr <omni::core::model::expression> expr) -> void {
        b.appendStatement (decl);
        b.prependStatement (expr);
    });
}

BOOST_AUTO_TEST_CASE (insertStatementAfter)
{
    buildModule (true,
                 [] (omni::core::model::block & b,
                     std::shared_ptr <omni::core::model::variable_declaration_expression> decl,
                     std::shared_ptr <omni::core::model::expression> expr) -> void {
        b.prependStatement (decl);
        b.insertStatementAfter (b.findStatement (decl), expr);
    });
    buildModule (false,
                 [] (omni::core::model::block & b,
                     std::shared_ptr <omni::core::model::variable_declaration_expression> decl,
                     std::shared_ptr <omni::core::model::expression> expr) -> void {
        b.prependStatement (expr);
        b.insertStatementAfter (b.findStatement (expr), decl);
    });
}

BOOST_AUTO_TEST_CASE (insertStatementBefore)
{
    buildModule (true,
                 [] (omni::core::model::block & b,
                     std::shared_ptr <omni::core::model::variable_declaration_expression> decl,
                     std::shared_ptr <omni::core::model::expression> expr) -> void {
        b.prependStatement (expr);
        b.insertStatementBefore (b.findStatement (expr), decl);
    });
    buildModule (false,
                 [] (omni::core::model::block & b,
                     std::shared_ptr <omni::core::model::variable_declaration_expression> decl,
                     std::shared_ptr <omni::core::model::expression> expr) -> void {
        b.prependStatement (decl);
        b.insertStatementBefore (b.findStatement (decl), expr);
    });
}

BOOST_AUTO_TEST_CASE (removeStatementFromPosition)
{
    buildModule (true,
                 [] (omni::core::model::block & b,
                     std::shared_ptr <omni::core::model::variable_declaration_expression> decl,
                     std::shared_ptr <omni::core::model::expression> expr) -> void {
        b.appendStatement (expr);
        b.appendStatement (decl);
        b.appendStatement (std::make_shared <omni::core::model::variable_expression> (decl));
        // Remove the first expression that uses the variable before it's declaration:
        b.removeStatement (b.findStatement (expr));
    });
    buildModule (false,
                 [] (omni::core::model::block & b,
                     std::shared_ptr <omni::core::model::variable_declaration_expression> decl,
                     std::shared_ptr <omni::core::model::expression> expr) -> void {
        b.appendStatement (expr);
        b.appendStatement (decl);
        auto expression = std::make_shared <omni::core::model::variable_expression> (decl);
        b.appendStatement (expression);
        // Remove the last expression, so that the expression that uses the variable before it's declaration stays:
        b.removeStatement (b.findStatement (expression));
    });
}

BOOST_AUTO_TEST_CASE (removeStatement)
{
    buildModule (true,
                 [] (omni::core::model::block & b,
                     std::shared_ptr <omni::core::model::variable_declaration_expression> decl,
                     std::shared_ptr <omni::core::model::expression> expr) -> void {
        b.appendStatement (expr);
        b.appendStatement (decl);
        b.appendStatement (std::make_shared <omni::core::model::variable_expression> (decl));
        // Remove the first expression that uses the variable before it's declaration:
        b.removeStatement (expr);
    });
    buildModule (false,
                 [] (omni::core::model::block & b,
                     std::shared_ptr <omni::core::model::variable_declaration_expression> decl,
                     std::shared_ptr <omni::core::model::expression> expr) -> void {
        b.appendStatement (expr);
        b.appendStatement (decl);
        auto expression = std::make_shared <omni::core::model::variable_expression> (decl);
        b.appendStatement (expression);
        // Remove the last expression, so that the expression that uses the variable before it's declaration stays:
        b.removeStatement (expression);
    });
}

BOOST_AUTO_TEST_SUITE_END ()
