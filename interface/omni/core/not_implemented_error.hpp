#ifndef OMNI_CORE_NOT_IMPLEMENTED_ERROR_HPP
#define OMNI_CORE_NOT_IMPLEMENTED_ERROR_HPP

#include <omni/core/core.hpp>
#include <omni/core/logic_error.hpp>

#include <string>

#pragma warning(push)
#pragma warning(disable:4275)

namespace omni {
namespace core {

    class OMNI_CORE_API not_implemented_error : public omni::core::logic_error {
    public:
        not_implemented_error (std::string const & fileName, std::string const & functionName, int lineNumber);
    };

} // namespace core
} // namespace omni

#pragma warning(pop)

#endif // include guard
