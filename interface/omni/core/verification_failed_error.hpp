#ifndef OMNI_CORE_VERIFICATION_FAILED_ERROR_HPP
#define OMNI_CORE_VERIFICATION_FAILED_ERROR_HPP

#include <omni/core/core.hpp>

#include <stdexcept>
#include <string>

#pragma warning(push)
#pragma warning(disable:4275)

namespace omni {
namespace core {

    /**
    Is thrown when a module is tried to be emitted, but the verification failed.
    **/
    class OMNI_CORE_API verification_failed_error : public std::runtime_error {
    public:
        verification_failed_error (std::string moduleName, std::string verificationErrorInfo);
    };

}
}

#pragma warning(pop)

#endif // include guard
