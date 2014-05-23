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
#include <stack>

#include <boost/test/unit_test.hpp>


#if 0
BOOST_AUTO_TEST_SUITE (inputStateTests)

BOOST_AUTO_TEST_CASE (basic)
{
    using namespace omni::core;

    auto statementElement = std::make_shared <input::abstract_syntax_element> ();

    auto ifSyntaxElement (std::make_shared <input::concrete_syntax_element> ());
    auto a = std::make_shared <input::fixed_template_element> (* ifSyntaxElement, 0, "if");
    auto b = std::make_shared <input::fixed_template_element> (* ifSyntaxElement, 1, " (");
    auto c = std::make_shared <input::syntax_template_element> (* ifSyntaxElement, 2, statementElement);
    auto d = std::make_shared <input::fixed_template_element> (* ifSyntaxElement, 3, ") {\n");
    auto e = std::make_shared <input::syntax_template_element> (* ifSyntaxElement, 4, statementElement);
    auto f = std::make_shared <input::fixed_template_element> (* ifSyntaxElement, 5, "}\n");
    auto ifTemplates = std::vector <std::shared_ptr <input::template_element>> {
        a, b, c, d, e, f,
    };
    ifSyntaxElement->setTemplates (ifTemplates);

    auto returnSyntaxElement = std::make_shared <input::concrete_syntax_element> ();
    auto returnTemplate1 = std::make_shared <input::fixed_template_element> (* returnSyntaxElement, 0, "return ");
    auto returnTemplate2 = std::make_shared <input::syntax_template_element> (* returnSyntaxElement, 1, statementElement);
    returnSyntaxElement->setTemplates (
        std::vector <std::shared_ptr <input::template_element>> {
            returnTemplate1,
            returnTemplate2,
        });

    auto whileSyntaxElement = std::make_shared <input::concrete_syntax_element> ();
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
        whileTemplate5
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
    // with the desired output of "if (foo) return foo":
    std::vector <std::tuple <std::string, int, bool>> simulatedInput {
        std::tuple <std::string, int, bool> ("i",  0, false),   // "if (...)"
        std::tuple <std::string, int, bool> ("fo", 0, true),    // "foo"
        std::tuple <std::string, int, bool> ("w",  0, false),   // "while (...)"
        std::tuple <std::string, int, bool> ("f",  0, true),    // "foo"
        std::tuple <std::string, int, bool> ("r",  0, false),   // "return ..."
        std::tuple <std::string, int, bool> ("f",  0, true),    // "foo"
    };

    std::stack <std::pair <input::syntax_element *, std::size_t>> suggestionStack;
    suggestionStack.push (std::make_pair (statementElement.get (), 0u));
    std::string output;
    for (auto i : simulatedInput) {
        if (suggestionStack.empty ()) {
            break;
        }
        auto suggestionInfo = suggestionStack.top ();        
        std::string input = std::get <0> (i);
        std::vector <input::syntax_suggestion> suggestions = suggestionInfo.first->suggest (input, suggestionInfo.second);
        int selectedIndex = std::get <1> (i);
        input::syntax_suggestion & suggestion = suggestions [selectedIndex];
        if (output.empty ()) {
            output = suggestion.text;
        } else {
            output += " " + suggestion.text;
        }
        if (!std::get <2> (i)) {
            input::syntax_element * elem = suggestion.syntaxElement;
            std::size_t templateIndex = suggestion.templateIndex;
            suggestionStack.push (std::make_pair (elem, templateIndex));
            if (std::shared_ptr <input::template_element> templateElement = elem->templateElementAt (suggestion.templateIndex)) {
                if (std::shared_ptr <input::syntax_element> syntaxElement = templateElement->dive ()) {
                    // We can do .get () here, because templateElement will live long enough for elem to stay:
                    suggestionStack.push (std::make_pair (syntaxElement.get (), 0u));
                }
            }
        } else {
            suggestionStack.pop ();
        }
    }
    BOOST_CHECK_EQUAL (output, "if foo return  foo");
}

BOOST_AUTO_TEST_SUITE_END ()

#endif
