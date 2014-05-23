#ifndef OMNI_CORE_CONCRETE_SYNTAX_ELEMENT_HPP
#define OMNI_CORE_CONCRETE_SYNTAX_ELEMENT_HPP

#include <omni/core/core.hpp>
#include <omni/core/input/syntax_element.hpp>

#include <vector>
#include <memory>

namespace omni {
namespace core {
namespace input {
class template_element;

/**
**/
class OMNI_CORE_API concrete_syntax_element : public syntax_element {
public:
    concrete_syntax_element (int indentationModifier = 0);

    std::shared_ptr <template_element> templateElementAt (std::size_t templatePosition) override;
    std::size_t templateElementCount () const override;

    void setTemplates (std::vector <std::shared_ptr <template_element>> templates);

    std::vector <syntax_suggestion> suggest (std::string input, std::size_t templatePosition = 0u) override;

private:
    std::vector <std::shared_ptr <template_element>> _templates;
    int _indentationModifier;
};

} // namespace input
} // namespace core
} // namespace omni

#endif // include guard
