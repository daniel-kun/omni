#include <omni/core/parser.hpp>
#include <omni/core/context.hpp>
#include <omni/core/model/module.hpp>
#include <omni/core/model/builtin_literal_expression.hpp>
#include <omni/core/model/variable_declaration_expression.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (parserTests)

BOOST_AUTO_TEST_CASE (builtinLiteral)
{
    omni::core::context c;
    omni::core::model::module m (c);

    omni::core::parser::ExpressionList expressions = omni::core::parser::parseExpression (m, "1234");

    BOOST_CHECK_EQUAL (expressions.size (), 1u);
    if (expressions.size () == 1) {
        omni::core::parser::parser_result <omni::core::model::expression> parserResult = * expressions.begin ();
        BOOST_CHECK (! parserResult.exact); // Meanwhile, exact is always set to false until it gets a meaning.
        BOOST_CHECK (parserResult.entity.get () != nullptr);
        std::shared_ptr <omni::core::model::expression> expression = parserResult.entity;
        using testIntType = unsigned int; // Currently, omni::core::parser only returns unsigned int literals.
        BOOST_CHECK_EQUAL (& expression->getMetaInfo (), & omni::core::model::builtin_literal_expression <unsigned int>::getStaticMetaInfo ());
        auto builtinLiteral = std::dynamic_pointer_cast <omni::core::model::builtin_literal_expression <unsigned int>> (expression);
        BOOST_CHECK (builtinLiteral.get () != nullptr);
        BOOST_CHECK_EQUAL (builtinLiteral->getValue (), 1234u);
    }
}

BOOST_AUTO_TEST_CASE (variableDeclarationExpression)
{
    omni::core::context c;
    omni::core::model::module m (c);

    omni::core::parser::ExpressionList expressions = omni::core::parser::parseExpression (m, "var ");
    BOOST_CHECK_EQUAL (expressions.size (), 1u);
    if (expressions.size () == 1) {
        omni::core::parser::parser_result <omni::core::model::expression> parserResult = * expressions.begin ();
        BOOST_CHECK (! parserResult.exact); // Meanwhile, exact is always set to false until it gets a meaning.
        BOOST_CHECK (parserResult.entity.get () != nullptr);
        std::shared_ptr <omni::core::model::expression> expression = parserResult.entity;
        BOOST_CHECK_EQUAL (& expression->getMetaInfo (), & omni::core::model::variable_declaration_expression::getStaticMetaInfo ());
        auto variableDecl = std::dynamic_pointer_cast <omni::core::model::variable_declaration_expression> (expression);
        BOOST_CHECK (variableDecl.get () != nullptr);
        BOOST_CHECK_EQUAL (variableDecl->getName (), "");
        BOOST_CHECK (variableDecl->getInitializationExpression ().get () == nullptr);
    }
}

BOOST_AUTO_TEST_SUITE_END ()
