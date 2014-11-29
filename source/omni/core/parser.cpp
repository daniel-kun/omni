#include <omni/core/parser.hpp>
#include <omni/core/not_implemented_error.hpp>
#include <omni/core/tools/string.hpp>
#include <omni/core/model/builtin_literal_expression.hpp>
#include <omni/core/model/variable_declaration_expression.hpp>

#include <cctype>
#include <sstream>

namespace {
const std::string startIf = "if(";
const std::string startVar = "var ";
}

/**
@brief Parses text and tries to interpret it as a statement. Since names can be ambiguous, a list of possible statements is returned.

These are the statement types that can be returned:
- if_statement
- return_statement
- while_statement
- do_while_statement

Plus all expression types. @see parseExpression()
@param scope The scope that is used to look up entity names.
@param text The text that is to parse into a statement, expression or candidates.
@result A list of possible statements that `text' could be interpreted as.
**/
omni::core::parser::StatementList omni::core::parser::parseStatement (omni::core::model::scope & scope, std::string const & text)
{
    if (tools::starts_with (text, startIf)) {
        return parseIfStatement (scope, text.substr (startIf.size ()));
    }
    auto expressions = parseExpression (scope, text);
    StatementList result;
    for (auto parserExpression : expressions) {
        result.push_back (parser_result <omni::core::model::statement> { parserExpression.entity, parserExpression.exact });
    }
    return result;
}

/**
@brief Parses text as an if-statement, while text is guaranteed to start with "if(".
@param scope The scope that is used to look up entity names.
@param text The text that is to parse into an if-statement or candidates.
@return Either an empty list or a list with exactly one element that is an omni::core::model::if_statement.
**/
omni::core::parser::StatementList omni::core::parser::parseIfStatement (omni::core::model::scope & scope, std::string const & text)
{
    throw not_implemented_error (__FILE__, __FUNCTION__, __LINE__);
}

/*
[ ] external_function
[ ] function
[ ] parameter
[ ] block
[ ] function_call_expression
[ ] variable_assignment_expression
[ ] binary_operator_expression
[ ] bitcast_expression
[ ] builtin_literal_expression
[ ] variable_declaration_expression
[ ] variable_expression
[ ] if_statement
[ ] return_statement
[ ] while_statement
[ ] do_while_statement
*/
omni::core::parser::ExpressionList omni::core::parser::parseExpression (omni::core::model::scope & scope, std::string const & text)
{
    if (text.size () == 0u) {
        return omni::core::parser::ExpressionList ();
    }
    if (omni::core::tools::is_numeric (text)) {
        return parseBuiltinLiteral (scope, text);
    }
    if (tools::starts_with (text, startVar)) {
        auto result = parseVariableDeclaration (scope, text);
        if (result.size () > 0) {
            return result;
        } // else: Try to parse it as something else...
    }
    return omni::core::parser::ExpressionList ();
}

/**
@brief Parses text as an variable declaration expression, while text is guaranteed to start with "var ".
**/
omni::core::parser::ExpressionList omni::core::parser::parseVariableDeclaration(omni::core::model::scope & scope, std::string const & text)
{
    std::string rest = text.substr (startVar.size ());
    std::size_t separator = rest.find ('=');
    ExpressionList initExpression;
    std::string varName = rest.substr (0, separator);
    if (separator != std::string::npos) {
        std::string initExpressionText = rest.substr (separator + 1);
        initExpression = parseExpression (scope, initExpressionText);

    }
    std::shared_ptr <omni::core::model::variable_declaration_expression> varDecl;
    if (initExpression.size () == 1) {
        varDecl = std::make_shared <omni::core::model::variable_declaration_expression> (initExpression [0].entity->getType ());
    } else {
        varDecl = std::make_shared <omni::core::model::variable_declaration_expression> ();
    }
    varDecl->setName (varName);
    return ExpressionList { parser_result <omni::core::model::expression> { varDecl, false } };
}

omni::core::parser::ExpressionList omni::core::parser::parseBuiltinLiteral (omni::core::model::scope & scope, std::string const & text)
{
    std::stringstream str (text);
    unsigned int value; // TODO: Determine and use the type encoded in the text.
    if (str >> value) {
        return ExpressionList { parser_result <omni::core::model::expression> { std::make_shared <omni::core::model::builtin_literal_expression <unsigned int>> (* scope.getContext (), value), false } };
    } else {
        return ExpressionList ();
    }
}
