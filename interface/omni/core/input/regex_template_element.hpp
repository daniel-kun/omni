#ifndef OMNI_CORE_REGEX_TEMPLATE_ELEMENT_HPP
#define OMNI_CORE_REGEX_TEMPLATE_ELEMENT_HPP

#include <omni/core/core.hpp>
#include <omni/core/input/template_element.hpp>

#include <string>

namespace omni {
namespace core {
namespace input {

/**
**/
class OMNI_CORE_API regex_template_element : public template_element {
public:
    regex_template_element (std::string regex);

    void visit (template_visitor & visitor) override;
};

} // namespace input
} // namespace core
} // namespace omni

#endif // include guard
