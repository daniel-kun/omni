#ifndef OMNI_CORE_FIXED_TEMPLATE_ELEMENT_HPP
#define OMNI_CORE_FIXED_TEMPLATE_ELEMENT_HPP

#include <omni/core/core.hpp>
#include <omni/core/input/template_element.hpp>

#include <string>

namespace omni {
namespace core {
namespace input {

/**
**/
class OMNI_CORE_API fixed_template_element : public template_element {
public:
    fixed_template_element (syntax_element & parent, std::size_t templateIndex, std::string text);

    std::vector <std::string> suggest (std::string input) override;
    
private:
    std::string _text;
};

} // namespace input
} // namespace core
} // namespace omni

#endif // include guard
