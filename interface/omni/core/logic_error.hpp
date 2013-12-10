#ifndef OMNI_CORE_LOGIC_ERROR_HPP
#define OMNI_CORE_LOGIC_ERROR_HPP

#include <omni/core/core.hpp>

#include <stdexcept>
#include <string>

#pragma warning(push)
#pragma warning(disable:4275)

namespace omni {
namespace core {

    class OMNI_CORE_API logic_error : public std::logic_error {
    public:
        logic_error (std::string const & fileName, std::string const & functionName, int lineNumber, std::string const & errorMessage);
    };

} // namespace core
} // namespace omni

#pragma warning(pop)

#endif // include guard
