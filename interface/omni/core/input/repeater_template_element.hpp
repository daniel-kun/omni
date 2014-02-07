#ifndef OMNI_CORE_REPEATER_TEMPLATE_ELEMENT_HPP
#define OMNI_CORE_REPEATER_TEMPLATE_ELEMENT_HPP

#include <omni/core/core.hpp>
#include <omni/core/input/template_element.hpp>

#include <memory>

namespace omni {
namespace core {
namespace input {

/**
**/
class OMNI_CORE_API repeater_template_element : public template_element {
public:
    repeater_template_element (std::shared_ptr <template_element> elementToBeRepeated);
};

} // namespace input
} // namespace core
} // namespace omni

#endif // include guard
