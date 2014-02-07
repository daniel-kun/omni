#include <omni/core/input/concrete_syntax_element.hpp>
#include <omni/core/input/template_element.hpp>

omni::core::input::concrete_syntax_element::concrete_syntax_element (int indentationModifier) :
    _templates (),
    _indentationModifier (indentationModifier)
{
}

std::shared_ptr <omni::core::input::template_element> omni::core::input::concrete_syntax_element::templatElementAt (std::size_t templatePosition)
{
    return _templates [templatePosition];
}

std::size_t omni::core::input::concrete_syntax_element::templateElementCount () const
{
    return _templates.size ();
}

void omni::core::input::concrete_syntax_element::setTemplates (std::vector <std::shared_ptr <template_element>> templates)
{
    _templates = templates;
}

std::vector <omni::core::input::syntax_suggestion> omni::core::input::concrete_syntax_element::suggest (std::string input, std::size_t templatePosition)
{
    std::size_t nextSyntaxTemplate = templatePosition;
    for (std::size_t i = nextSyntaxTemplate; i < _templates.size (); ++i) {
        if (_templates [i]->dive () != nullptr) {
            nextSyntaxTemplate = i;
            break;
        }
    }

    std::vector <syntax_suggestion> result;
    for (std::string text : _templates [templatePosition]->suggest (input)) {
        result.push_back (syntax_suggestion (* this, nextSyntaxTemplate, text));
    }
    std::shared_ptr <syntax_element> elem = _templates [templatePosition]->dive ();
    if (elem != nullptr) {
        std::vector <syntax_suggestion> elemSuggestions = elem->suggest (input, 0u);
        result.insert (result.end (), elemSuggestions.begin (), elemSuggestions.end ());
    }
    return result;
}
