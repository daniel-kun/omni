#ifndef OMNI_CORE_NO_CONTEXT_ERROR_HPP
#define OMNI_CORE_NO_CONTEXT_ERROR_HPP

#include <omni/core/core.hpp>
#include <omni/core/domain.hpp>

#include <stdexcept>

#pragma warning(push)
#pragma warning(disable:4275)

namespace omni {
namespace core {

    /**
    Is thrown when something was expected to be added to a context at this point (such as when compiling a function), but it was not yet added to a context.
    **/
    class OMNI_CORE_API no_context_error : public std::runtime_error {
    public:
        no_context_error (domain domain, std::string const & identifier);
    };

} // namespace core
} // namespace omni

#pragma warning(pop)

#endif // include guard
