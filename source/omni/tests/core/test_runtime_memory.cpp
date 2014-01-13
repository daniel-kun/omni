#include <omni/core/runtime.hpp>
#include <omni/core/context.hpp>
#include <omni/core/module.hpp>
#include <omni/core/type.hpp>
#include <omni/core/function.hpp>
#include <omni/core/parameter.hpp>
#include <omni/core/block.hpp>
#include <omni/core/function_call_expression.hpp>
#include <omni/core/external_function.hpp>
#include <omni/core/return_statement.hpp>
#include <omni/core/literal_expression.hpp>
#include <omni/core/builtin_literal.hpp>
#include <omni/core/variable_declaration_expression.hpp>
#include <omni/core/variable_expression.hpp>
#include <omni/core/bitcast_expression.hpp>

#include <omni/tests/test_utils.hpp>

#include <memory>

#include <boost/test/auto_unit_test.hpp>

BOOST_AUTO_TEST_SUITE (coreRuntimeMemoryTests)

BOOST_AUTO_TEST_CASE (referenceCounting)
{
    using namespace omni::core;

    context c;
    module m (c, "test");
    runtime r (m);

    auto rawPtr= c.sharedBasicType (type_class::t_unsignedByte, 1);
    auto ptrInt32 = c.sharedBasicType (type_class::t_unsignedInt, 1);
    auto typeInt32 = c.sharedBasicType (type_class::t_unsignedInt);
    auto funcBody = std::make_shared <block> ();
    auto ptrVariable = std::make_shared <variable_declaration_expression> (
        std::make_shared <bitcast_expression> (
            std::make_shared <function_call_expression> (
                r.getMemoryAllocate (),
                std::vector <std::shared_ptr <expression>> {
                    std::make_shared <literal_expression> (std::make_shared <builtin_literal<unsigned int>> (c, 128))
                }),
            ptrInt32));
    // Allocate memory:
    funcBody->appendStatement (ptrVariable);
    // Increment the reference counter to 2:
    funcBody->appendStatement (
        std::make_shared <function_call_expression> (
            r.getMemoryAddReference (),
            std::vector <std::shared_ptr <expression>> {
                std::make_shared <bitcast_expression> (
                    std::make_shared <variable_expression> (ptrVariable),
                    rawPtr)
            }));
    // Decrement the reference counter to 1:
    funcBody->appendStatement (
        std::make_shared <function_call_expression> (
            r.getMemoryRemoveReference (),
            std::vector <std::shared_ptr <expression>> {
                std::make_shared <bitcast_expression> (
                    std::make_shared <variable_expression> (ptrVariable),
                    rawPtr)
            }));
    // Decrement the reference counter to 0 (memory will be freed):
    funcBody->appendStatement (
        std::make_shared <return_statement> (
            std::make_shared <bitcast_expression> (
                std::make_shared <function_call_expression> (
                    r.getMemoryRemoveReference (),
                    std::vector <std::shared_ptr <expression>> {
                        std::make_shared <bitcast_expression> (
                            std::make_shared <variable_expression> (ptrVariable),
                            rawPtr)
                    }),
                ptrInt32)));
    std::shared_ptr<function> func = m.createFunction ("test", ptrInt32, funcBody);

    omni::tests::test_file_manager testFileManager;
    int * result = omni::tests::runFunction <int*> (func, testFileManager, "runtimeMemoryReferenceCounting");
    BOOST_CHECK (result == nullptr);
}

BOOST_AUTO_TEST_SUITE_END ()
