#ifndef OMNI_CORE_INPUT_VARIABLE_TEMPLATE_PROVIDER_HPP
#define OMNI_CORE_INPUT_VARIABLE_TEMPLATE_PROVIDER_HPP

#include <omni/core/core.hpp>

#include <string>
#include <vector>

namespace omni {
namespace core {
namespace input {

/**
**/
class OMNI_CORE_API variable_template_provider {
public:
    virtual std::vector <std::string> provide (std::string input) = 0;
};

} // namespace input
} // namespace core
} // namespace omni

#endif // include guard
