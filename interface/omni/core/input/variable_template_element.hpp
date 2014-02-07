#ifndef OMNI_CORE_VARIABLE_TEMPLATE_ELEMENT_HPP
#define OMNI_CORE_VARIABLE_TEMPLATE_ELEMENT_HPP

#include <omni/core/core.hpp>
#include <omni/core/input/template_element.hpp>
#include <omni/core/input/template_variables.hpp>

namespace omni {
namespace core {
namespace input {
class variable_template_provider;

/**
**/
class OMNI_CORE_API variable_template_element : public template_element {
public:
    variable_template_element (
        syntax_element & parent,
        std::size_t templateIndex,
        variable_template_provider & provider);

    std::vector <std::string> suggest (std::string input) override;

private:
    variable_template_provider & _provider;
};

} // namespace input
} // namespace core
} // namespace omni

#endif // include guard
