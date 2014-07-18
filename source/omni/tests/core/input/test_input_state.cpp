#include <omni/core/input/abstract_syntax_element.hpp>
#include <omni/core/input/template_element.hpp>
#include <omni/core/input/fixed_template_element.hpp>
#include "test_utils_input.hpp"

#include <boost/test/unit_test.hpp>

#include <tuple>
#include <vector>
#include <string>
#include <utility>

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

    std::shared_ptr <input::syntax_element> statementElement = omni::tests::makeTestSyntaxElement ();

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
