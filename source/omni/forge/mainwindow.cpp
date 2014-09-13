#include <omni/forge/mainwindow.hpp>
#include <omni/core/input/abstract_syntax_element.hpp>
#include <omni/core/input/concrete_syntax_element.hpp>
#include <omni/core/input/fixed_template_element.hpp>
#include <omni/core/input/variable_template_element.hpp>
#include <omni/core/input/variable_template_provider.hpp>
#include <omni/core/input/syntax_template_element.hpp>
#include <omni/core/input/template_visitor.hpp>

auto statementSyntaxElement = std::make_shared <omni::core::input::abstract_syntax_element> ();

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

namespace {
void initStatementSyntaxElement ()
{
    using namespace omni::core;

    auto ifSyntaxElement (std::make_shared <input::concrete_syntax_element> ());
    auto a = std::make_shared <input::fixed_template_element> (* ifSyntaxElement, 0, "if");
    auto b = std::make_shared <input::fixed_template_element> (* ifSyntaxElement, 1, " (");
    auto c = std::make_shared <input::syntax_template_element> (* ifSyntaxElement, 2, statementSyntaxElement);
    auto d = std::make_shared <input::fixed_template_element> (* ifSyntaxElement, 3, ") {\n");
    auto e = std::make_shared <input::syntax_template_element> (* ifSyntaxElement, 4, statementSyntaxElement);
    auto f = std::make_shared <input::fixed_template_element> (* ifSyntaxElement, 5, "}\n");
    auto ifTemplates = std::vector <std::shared_ptr <input::template_element>> {
        a, b, c, d, e, f,
    };
    ifSyntaxElement->setTemplates (ifTemplates);

    auto returnSyntaxElement = std::make_shared <input::concrete_syntax_element> ();
    auto returnTemplate1 = std::make_shared <input::fixed_template_element> (* returnSyntaxElement, 0, "return ");
    auto returnTemplate2 = std::make_shared <input::syntax_template_element> (* returnSyntaxElement, 1, statementSyntaxElement);
    returnSyntaxElement->setTemplates (
        std::vector <std::shared_ptr <input::template_element>> {
            returnTemplate1,
            returnTemplate2,
        });

    auto whileSyntaxElement = std::make_shared <input::concrete_syntax_element> ();
    auto whileTemplate1 = std::make_shared <input::fixed_template_element> (* whileSyntaxElement, 0, "while");
    auto whileTemplate2 = std::make_shared <input::fixed_template_element> (* whileSyntaxElement, 1, " (");
    auto whileTemplate3 = std::make_shared <input::syntax_template_element> (* whileSyntaxElement, 2, statementSyntaxElement);
    auto whileTemplate4 = std::make_shared <input::fixed_template_element> (* whileSyntaxElement, 3, ") {\n");
    auto whileTemplate5 = std::make_shared <input::syntax_template_element> (* whileSyntaxElement, 4, statementSyntaxElement);
    auto whileTemplate6 = std::make_shared <input::fixed_template_element> (* whileSyntaxElement, 5, "}\n");

    whileSyntaxElement->setTemplates (
        std::vector <std::shared_ptr <input::template_element>> {
        whileTemplate1,
        whileTemplate2,
        whileTemplate3,
        whileTemplate4,
        whileTemplate5
        });

    auto variableSyntaxElement = std::make_shared <input::concrete_syntax_element> ();
    auto variableTemplate1 = std::make_shared <input::variable_template_element> (* variableSyntaxElement, 0, testVariableProvider);
    variableSyntaxElement->setTemplates (
        std::vector <std::shared_ptr <input::template_element>> {
            variableTemplate1
        });

    statementSyntaxElement->setPossibleSubstitutions (
        std::vector <std::shared_ptr <input::syntax_element>> {
            ifSyntaxElement,
            returnSyntaxElement,
            whileSyntaxElement,
            variableSyntaxElement
        });
}
}

omni::forge::MainWindow::MainWindow () :
    _layout (this),
    _blueprint (this),
    _syntaxInput (this, * statementSyntaxElement)
{
    _layout.setMargin (0);
    _layout.addWidget (& _blueprint, 0, 0);
    _layout.addWidget (& _syntaxInput, 0, 0);

    resize (400, 500);

    initStatementSyntaxElement ();
}
