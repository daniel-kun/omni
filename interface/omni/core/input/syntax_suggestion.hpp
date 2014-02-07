#ifndef OMNI_CORE_SYNTAX_SUGGESTION_HPP
#define OMNI_CORE_SYNTAX_SUGGESTION_HPP

#include <omni/core/core.hpp>

#include <memory>
#include <string>

namespace omni {
namespace core {
namespace input {
    class syntax_element;

/**
**/
class OMNI_CORE_API syntax_suggestion {
public:
    syntax_suggestion (syntax_element & syntaxElement, std::size_t templateIndex, std::string text);

    syntax_element * syntaxElement;
    std::size_t templateIndex;
    std::string text;
};

} // namespace input
} // namespace core
} // namespace omni

#endif // include guard
