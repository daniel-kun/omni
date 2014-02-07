#ifndef OMNI_CORE_SYNTAX_TEMPLATE_ELEMENT_HPP
#define OMNI_CORE_SYNTAX_TEMPLATE_ELEMENT_HPP

#include <omni/core/core.hpp>
#include <omni/core/input/template_element.hpp>

#include <memory>

namespace omni {
namespace core {
namespace input {
class syntax_element;

/**
**/
class OMNI_CORE_API syntax_template_element : public template_element {
public:
    syntax_template_element (syntax_element & parent, std::size_t templateIndex, std::shared_ptr <syntax_element> target);

    std::vector <std::string> suggest (std::string input) override;

    std::shared_ptr <syntax_element> dive ();

    std::shared_ptr <syntax_element> getSyntaxElement () const;

private:
    std::shared_ptr <syntax_element> _target;
};

} // namespace input
} // namespace core
} // namespace omni

#endif // include guard
