#include <omni/core/input/concrete_syntax_element.hpp>
#include <omni/core/input/template_element.hpp>

omni::core::input::concrete_syntax_element::concrete_syntax_element (int indentationModifier) :
    _templates (),
    _indentationModifier (indentationModifier)
{
}

std::shared_ptr <omni::core::input::template_element> omni::core::input::concrete_syntax_element::templateElementAt (std::size_t templatePosition)
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

std::vector <omni::core::input::syntax_suggestion> omni::core::input::concrete_syntax_element::suggestImpl (std::string input, std::size_t templatePosition, std::set <syntax_element *> alreadyVisistedElements)
{
    if (alreadyVisistedElements.find (this) != alreadyVisistedElements.end ()) {
         return std::vector <omni::core::input::syntax_suggestion> ();
    }
    alreadyVisistedElements.insert (this);
    // Find the next template that "goes one level deeper":
    std::size_t nextSyntaxTemplate = templatePosition;
    for (std::size_t i = nextSyntaxTemplate; i < _templates.size (); ++i) {
        if (_templates [i]->dive () != nullptr) {
            nextSyntaxTemplate = i;
            break;
        }
    }

    // Make my own suggestions first:
    std::vector <syntax_suggestion> result;
    for (std::string text : _templates [templatePosition]->suggest (input)) {
        result.push_back (syntax_suggestion (* this, nextSyntaxTemplate, text));
    }
    // And then the suggestions of the underlying syntax_element at the given template position:
    std::shared_ptr <syntax_element> elem = _templates [templatePosition]->dive ();
    if (elem != nullptr) {
        std::vector <syntax_suggestion> elemSuggestions = elem->suggestImpl (input, 0u, alreadyVisistedElements);
        result.insert (result.end (), elemSuggestions.begin (), elemSuggestions.end ());
    }
    return result;
}
