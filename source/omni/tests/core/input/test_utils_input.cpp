#include "test_utils_input.hpp"
#include <omni/core/input/syntax_element.hpp>
#include <omni/core/input/abstract_syntax_element.hpp>
#include <omni/core/input/concrete_syntax_element.hpp>
#include <omni/core/input/syntax_template_element.hpp>
#include <omni/core/input/fixed_template_element.hpp>
#include <omni/core/input/variable_template_element.hpp>
#include <omni/core/input/variable_template_provider.hpp>

namespace {

    class test_variable_provider : public omni::core::input::variable_template_provider {
    public:
        test_variable_provider ()
        {
            _variables.push_back ("foo");
        }

        std::vector <std::string> provide (std::string input) override {
            std::vector <std::string> result;
            for (auto i : _variables) {
                if (i.find (input) == 0u) {
                    result.push_back (i);
                }
            }
            return result;
        }

    private:
        std::vector <std::string> _variables;
    } testVariableProvider;

}
/**
Returns an syntax_element that contains some demo content:
- if (<statement>) { <statement> }
- while (<statement>) { statement> }
- variable "foo"
- return <statement>

**/
std::shared_ptr <omni::core::input::syntax_element> omni::tests::makeTestSyntaxElement ()
{
    using namespace omni::core;

    auto statementElement = std::make_shared <input::abstract_syntax_element> ();
    statementElement->setName ("root_statement");

    auto ifSyntaxElement (std::make_shared <input::concrete_syntax_element> ());
    ifSyntaxElement->setName ("if_statement");
    auto a = std::make_shared <input::fixed_template_element>  (* ifSyntaxElement, 0, "if");
    auto b = std::make_shared <input::fixed_template_element>  (* ifSyntaxElement, 1, " (");
    auto c = std::make_shared <input::syntax_template_element> (* ifSyntaxElement, 2, statementElement);
    auto d = std::make_shared <input::fixed_template_element>  (* ifSyntaxElement, 3, ") {\n");
    auto e = std::make_shared <input::syntax_template_element> (* ifSyntaxElement, 4, statementElement);
    auto f = std::make_shared <input::fixed_template_element>  (* ifSyntaxElement, 5, "}\n");
    auto ifTemplates = std::vector <std::shared_ptr <input::template_element>> {
        a, b, c, d, e, f,
    };
    ifSyntaxElement->setTemplates (ifTemplates);

    auto returnSyntaxElement = std::make_shared <input::concrete_syntax_element> ();
    returnSyntaxElement->setName ("return_statement");
    auto returnTemplate1 = std::make_shared <input::fixed_template_element> (* returnSyntaxElement, 0, "return ");
    auto returnTemplate2 = std::make_shared <input::syntax_template_element> (* returnSyntaxElement, 1, statementElement);
    auto returnTemplate3 = std::make_shared <input::fixed_template_element> (* returnSyntaxElement, 2, "\n");
    returnSyntaxElement->setTemplates (
        std::vector <std::shared_ptr <input::template_element>> {
            returnTemplate1,
            returnTemplate2,
            returnTemplate3,
        });

    auto whileSyntaxElement = std::make_shared <input::concrete_syntax_element> ();
    whileSyntaxElement->setName ("while_statement");
    auto whileTemplate1 = std::make_shared <input::fixed_template_element> (* whileSyntaxElement, 0, "while");
    auto whileTemplate2 = std::make_shared <input::fixed_template_element> (* whileSyntaxElement, 1, " (");
    auto whileTemplate3 = std::make_shared <input::syntax_template_element> (* whileSyntaxElement, 2, statementElement);
    auto whileTemplate4 = std::make_shared <input::fixed_template_element> (* whileSyntaxElement, 3, ") {\n");
    auto whileTemplate5 = std::make_shared <input::syntax_template_element> (* whileSyntaxElement, 4, statementElement);
    auto whileTemplate6 = std::make_shared <input::fixed_template_element> (* whileSyntaxElement, 5, "}\n");

    whileSyntaxElement->setTemplates (
        std::vector <std::shared_ptr <input::template_element>> {
        whileTemplate1,
        whileTemplate2,
        whileTemplate3,
        whileTemplate4,
        whileTemplate5,
        whileTemplate6
        });

    auto variableSyntaxElement = std::make_shared <input::concrete_syntax_element> ();
    variableSyntaxElement->setName ("variable_statement");
    auto variableTemplate1 = std::make_shared <input::variable_template_element> (* variableSyntaxElement, 0, testVariableProvider);
    variableSyntaxElement->setTemplates (
        std::vector <std::shared_ptr <input::template_element>> {
            variableTemplate1
        });

    statementElement->setPossibleSubstitutions (
        std::vector <std::shared_ptr <input::syntax_element>> {
            ifSyntaxElement,
            returnSyntaxElement,
            whileSyntaxElement,
            variableSyntaxElement
        });
    return statementElement;
}
