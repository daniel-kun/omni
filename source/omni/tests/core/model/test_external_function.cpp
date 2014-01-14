#include <omni/core/model/external_function.hpp>
#include <omni/core/model/block.hpp>
#include <omni/core/context.hpp>
#include <omni/core/module.hpp>
#include <omni/core/model/type.hpp>
#include <omni/core/model/builtin_literal.hpp>
#include <omni/core/model/literal_expression.hpp>
#include <omni/core/model/function.hpp>
#include <omni/core/model/parameter.hpp>
#include <omni/core/model/function_call_expression.hpp>

#include <omni/tests/test_utils.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (externalFunctionTests)

BOOST_AUTO_TEST_CASE (ctor)
{
    using namespace omni::core;
    context c;
    module mod (c, "test");
    std::shared_ptr <model::external_function> function_putchar (new model::external_function (mod, "LIBCMT.LIB", "putchar", model::type::sharedBasicType (c, model::type_class::t_signedInt)));
    std::shared_ptr <model::parameter> param1 (new model::parameter (model::type::sharedBasicType (c, model::type_class::t_signedInt), std::string ()));
    function_putchar->addParameter (param1);

    std::shared_ptr <model::function_call_expression> functionCallExpression (new model::function_call_expression (function_putchar));
    std::shared_ptr <model::builtin_literal <signed int>> param1Value (new model::builtin_literal <signed int> (c, 'O'));
    auto param1Type = param1Value->getType ();
    auto putcharParam1Type = function_putchar->getParameters () [0]->getType ();
    std::shared_ptr <model::literal_expression> param1Expression (new model::literal_expression (param1Value));
    functionCallExpression->addParameter (param1Expression);

    std::shared_ptr <model::block> body (new model::block ());
    std::shared_ptr <model::return_statement> returnStatement (new model::return_statement (functionCallExpression));
    body->appendStatement (returnStatement);
    std::shared_ptr <model::function> funcCaller (new model::function (mod, "putcharCaller", model::type::sharedBasicType (c, model::type_class::t_signedInt), body));

    mod.addFunction (function_putchar);
    mod.addFunction (funcCaller);

    omni::tests::test_file_manager testFileManager;
    std::string functionName;
    omni::tests::runFunction <int> (funcCaller, testFileManager, "externalFunctionTestsCtor");
}

BOOST_AUTO_TEST_SUITE_END ()
