#include <omni/core/input/abstract_syntax_element.hpp>
#include <omni/core/input/concrete_syntax_element.hpp>
#include <omni/core/input/variable_template_element.hpp>
#include <omni/core/input/variable_template_provider.hpp>
#include <omni/core/input/fixed_template_element.hpp>
#include <omni/core/input/regex_template_element.hpp>
#include <omni/core/input/repeater_template_element.hpp>
#include <omni/core/input/syntax_template_element.hpp>
#include <omni/core/input/template_variables.hpp>
#include <omni/core/id.hpp>

#include <tuple>
#include <vector>
#include <string>
#include <utility>

#include <boost/test/unit_test.hpp>

namespace {
std::string runInputSimulation (omni::core::input::syntax_element & statementElement, std::size_t templateIndex, std::vector <std::tuple <std::string, std::size_t>> & simulatedInput)
{
    using namespace omni::core;
    std::string output;
    while (simulatedInput.size () > 0) {
        std::tuple <std::string, std::size_t> input = simulatedInput.front ();
        simulatedInput.erase (simulatedInput.begin ());

        std::vector <input::syntax_suggestion> suggestions = statementElement.suggest (std::get <0> (input), templateIndex);
        BOOST_CHECK_GT (suggestions.size (), 0u);
        BOOST_CHECK_LT (std::get <1> (input), suggestions.size ());
        if (! suggestions.empty () && std::get <1> (input) < suggestions.size ()) {
            input::syntax_suggestion selectedSuggestion = suggestions [std::get <1> (input)];
            output += selectedSuggestion.text;
            if (selectedSuggestion.syntaxElement != nullptr) {
                input::syntax_element & selectedSyntaxElem = * selectedSuggestion.syntaxElement;
                for (std::size_t t = 1u; t < selectedSyntaxElem.templateElementCount (); ++t) {
                    std::shared_ptr <input::syntax_element> element = selectedSyntaxElem.templateElementAt (t)->dive ();
                    if (element != nullptr) {
                        output += runInputSimulation (* element, 0u, simulatedInput);
                    } else {
                        std::shared_ptr <input::fixed_template_element> textTemplateElement = std::dynamic_pointer_cast <input::fixed_template_element> (selectedSyntaxElem.templateElementAt (t));
                        if (textTemplateElement != nullptr) {
                            output += textTemplateElement->getText ();
                        }
                    }
                }
            }
        }
        break;
    }
    return output;
}

}

BOOST_AUTO_TEST_SUITE (inputStateTests)

BOOST_AUTO_TEST_CASE (basic)
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

    class test_variable_provider : public input::variable_template_provider {
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
    // Simulates the input of "i<tab>fo<tab>r<tab>f<tab>"
    // with the desired output of "if (foo) return foo"
    // first:  Text that has been typed
    // second: Index of the suggestion that has been accepted
    // third:  Dive into the suggested element, or step to the next element on the same level?
    std::vector <std::tuple <std::string, std::size_t>> simulatedInput {
        std::make_tuple ("i",  0u),   // "if (...)"
        std::make_tuple ("fo", 0u),    // "foo"
        std::make_tuple ("w",  0u),   // "while (...)"
        std::make_tuple ("f",  0u),    // "foo"
        std::make_tuple ("r",  0u),   // "return ..."
        std::make_tuple ("f",  0u),    // "foo"
    };

    std::string output = runInputSimulation (* statementElement, 0u, simulatedInput);
    std::string desiredOutput = R"(if (foo) {
while (foo) {
return foo
}
}
)";
    BOOST_CHECK_EQUAL (output, desiredOutput);
}

BOOST_AUTO_TEST_SUITE_END ()
