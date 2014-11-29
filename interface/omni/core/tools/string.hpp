#ifndef OMNI_CORE_TOOLS_STRING_HPP
#define OMNI_CORE_TOOLS_STRING_HPP

#include <omni/core/core.hpp>
#include <string>

namespace omni {
namespace core {
namespace tools {

bool OMNI_CORE_API starts_with (std::string const & string, std::string const & startText);
bool OMNI_CORE_API is_numeric (std::string const & string);

} // namespace tools
} // namespace core
} // namespace omni

#endif // include guard
