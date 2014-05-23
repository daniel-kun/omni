#ifndef OMNI_CORE_ABSTRACT_SYNTAX_ELEMENT_HPP
#define OMNI_CORE_ABSTRACT_SYNTAX_ELEMENT_HPP

#include <omni/core/core.hpp>
#include <omni/core/input/syntax_element.hpp>
#include <omni/core/input/syntax_suggestion.hpp>

#include <vector>
#include <memory>

namespace omni {
namespace core {
namespace input {

/**
**/
class OMNI_CORE_API abstract_syntax_element : public syntax_element {
public:
    abstract_syntax_element ();
    abstract_syntax_element (std::vector <std::shared_ptr <syntax_element>> possibleSubstitutions);

    std::vector <syntax_suggestion> suggest (std::string input, std::size_t templatePosition) override;

    void setPossibleSubstitutions (std::vector <std::shared_ptr <syntax_element>> possibleSubstitutions);
    std::vector <std::shared_ptr <syntax_element>> getPossibleSubstitutions () const;

private:
    std::vector <std::shared_ptr <syntax_element>> _possibleSubstitutions;
};

} // namespace input
} // namespace core
} // namespace omni

#endif // include guard
