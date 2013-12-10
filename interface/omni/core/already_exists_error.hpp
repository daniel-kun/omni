#ifndef OMNI_CORE_ALREADY_EXISTS_ERROR_HPP
#define OMNI_CORE_ALREADY_EXISTS_ERROR_HPP

#include <omni/core/core.hpp>
#include <omni/core/domain.hpp>

#include <stdexcept>

#pragma warning(push)
#pragma warning(disable:4275)

namespace omni {
namespace core {

    /**
    Is thrown when something was expected to not exist, but it existed.
    E.g. when adding a function to a class where a function with the same prototype already exists.
    **/
    class OMNI_CORE_API already_exists_error : public std::runtime_error {
    public:
        already_exists_error (domain domain, std::string const & identifier);
    };

} // namespace core
} // namespace omni

#pragma warning(pop)

#endif // include guard
