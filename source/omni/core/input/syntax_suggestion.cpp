#include <omni/core/input/syntax_suggestion.hpp>

omni::core::input::syntax_suggestion::syntax_suggestion (syntax_element & syntaxElement, std::size_t templateIndex, std::string text) :
    syntaxElement (& syntaxElement),
    templateIndex (templateIndex),
    text (text)
{
}
