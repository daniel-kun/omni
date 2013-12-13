#include <omni/core/external_function.hpp>
#include <omni/core/block.hpp>
#include <omni/core/context.hpp>
#include <omni/core/module.hpp>
#include <omni/core/type.hpp>
#include <omni/core/builtin_literal.hpp>
#include <omni/core/literal_expression.hpp>
#include <omni/core/function.hpp>
#include <omni/core/parameter.hpp>
#include <omni/core/function_call_expression.hpp>
#include <omni/core/expression_statement.hpp>

#include <omni/tests/test_utils.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (externalFunctionTests)

BOOST_AUTO_TEST_CASE (ctor)
{
    using namespace omni::core;
    context c;
    module mod (c, "test");
    std::shared_ptr <external_function> function_putchar (new external_function (mod, "LIBCMT.LIB", "putchar", type::sharedBasicType (c, type_class::t_signedInt)));
    std::shared_ptr <parameter> param1 (new parameter (type::sharedBasicType (c, type_class::t_signedInt), std::string ()));
    function_putchar->addParameter (param1);

    std::shared_ptr <function_call_expression> functionCallExpression (new function_call_expression (function_putchar));
    std::shared_ptr <builtin_literal <signed int>> param1Value (new builtin_literal <signed int> (c, 'O'));
    auto param1Type = param1Value->getType ();
    auto putcharParam1Type = function_putchar->getParameters () [0]->getType ();
    std::shared_ptr <literal_expression> param1Expression (new literal_expression (param1Value));
    functionCallExpression->addParameter (param1Expression);

    std::shared_ptr <block> body (new block ());
    std::shared_ptr <return_statement> returnStatement (new return_statement (functionCallExpression));
    body->appendStatement (returnStatement);
    std::shared_ptr <function> funcCaller (new function (mod, "putcharCaller", type::sharedBasicType (c, type_class::t_signedInt), body));

    mod.addFunction (function_putchar);
    mod.addFunction (funcCaller);

    omni::tests::test_file_manager testFileManager;
    std::string functionName;
    omni::tests::runFunction <int> (funcCaller, testFileManager, "externalFunctionTestsCtor");
}

BOOST_AUTO_TEST_SUITE_END ()
