#include <omni/core/input/input_state.hpp>
#include "test_utils_input.hpp"
#include <omni/core/input/syntax_element.hpp>
#include <omni/core/input/template_element.hpp>
#include <omni/core/input/fixed_template_element.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/signals2.hpp>

#include <stack>

namespace {
std::tuple <std::string, std::string> runInputSimulation (omni::core::input::syntax_element & statementElement, std::vector <std::string> & simulatedInput)
{
    using namespace omni::core;
    std::string output;
    std::string autoCompletion;
    while (simulatedInput.size () > 0) {
        std::string input = simulatedInput.front ();
        simulatedInput.erase (simulatedInput.begin ());

        std::vector <input::syntax_suggestion> suggestions = statementElement.suggest (input, 0u);
        BOOST_CHECK_GT (suggestions.size (), 0u);
        bool hasMoreInput = ! simulatedInput.empty ();
        if (! suggestions.empty ()) {
            input::syntax_suggestion selectedSuggestion = suggestions [0u];
            output += selectedSuggestion.text;
            if (selectedSuggestion.syntaxElement != nullptr) {
                input::syntax_element & selectedSyntaxElem = * selectedSuggestion.syntaxElement;
                for (std::size_t t = 1u; t < selectedSyntaxElem.templateElementCount (); ++t) {
                    std::shared_ptr <input::syntax_element> element = selectedSyntaxElem.templateElementAt (t)->dive ();
                    if (element != nullptr) {
                        if (hasMoreInput) {
                            auto inputResult = runInputSimulation (* element, simulatedInput);
                            output += std::get <0> (inputResult);
                        } else {
                            autoCompletion += "<" + element->getName () + ">";
                        }
                    } else {
                        std::shared_ptr <input::fixed_template_element> textTemplateElement = std::dynamic_pointer_cast <input::fixed_template_element> (selectedSyntaxElem.templateElementAt (t));
                        if (textTemplateElement != nullptr) {
                            if (hasMoreInput) {
                                output += textTemplateElement->getText ();
                            } else {
                                autoCompletion += textTemplateElement->getText ();
                            }
                        }
                    }
                }
            }
        }
        break;
    }
    return std::make_tuple (output, autoCompletion);
}
}

namespace omni {
namespace core {
namespace input {

class input_manager {
public:
    typedef boost::signals2::signal <void (std::string output, std::string suggestion)> on_output_changed_signal;

    input_manager ();

    on_output_changed_signal onOutputChanged;

    void accept ();
    void input (std::string text);
    void backspace ();

private:
    std::shared_ptr <syntax_element> _rootSyntaxElement;
    std::vector <std::string> _inputHistory;
    std::stack <syntax_element> _syntaxStack;
}; // class input_manager

} // namepace input
} // namepace core
} // namepace omni

omni::core::input::input_manager::input_manager () :
    _rootSyntaxElement (omni::tests::makeTestSyntaxElement ()),
    _inputHistory (),
    _syntaxStack ()
{
}

void omni::core::input::input_manager::accept ()
{
}

void omni::core::input::input_manager::input (std::string text)
{
    _inputHistory.push_back (text);
    std::tuple <std::string, std::string> result = runInputSimulation (*_rootSyntaxElement, _inputHistory);
    onOutputChanged (std::get <0> (result), std::get <1> (result));
}

void omni::core::input::input_manager::backspace ()
{
}

#if 0

BOOST_AUTO_TEST_SUITE (inputManagerTests)

BOOST_AUTO_TEST_CASE (basic)
{
    using namespace omni::core::input;

    std::string result;

    input_manager manager;
    boost::signals2::connection connection = manager.onOutputChanged.connect ([&result] (std::string output, std::string suggestion) -> void {
        result = output;
    });

    manager.input ("i");
    manager.accept ();
    manager.input ("fo");
    manager.accept ();
    manager.input ("w");
    manager.accept ();
    manager.input ("fo");
    manager.accept ();
    manager.input ("r");
    manager.accept ();
    manager.input ("f");
    manager.accept ();

    std::string desiredOutput = R"(if (foo) {
while (foo) {
return foo
}
}
)";
    BOOST_CHECK_EQUAL (result, desiredOutput);
}

BOOST_AUTO_TEST_SUITE_END ()

#endif
