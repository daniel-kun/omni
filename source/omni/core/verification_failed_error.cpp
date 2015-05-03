#include <omni/core/verification_failed_error.hpp>

#include <boost/format.hpp>

namespace {
    std::string buildVerificationFailedErrorMessage (std::string moduleName, std::string verificationErrorInfo)
    {
        return (boost::format ("Verification of module %1% failed:\n%2%") % moduleName % verificationErrorInfo).str ();
    }
}

/**
Initializes this verification_failed_error with an error message stating the verification of module with the given moduleName failed for the reasons
specified in the verificationErrorInfo.
**/
omni::core::verification_failed_error::verification_failed_error (std::string moduleName, std::string verificationErrorInfo) :
    std::runtime_error (buildVerificationFailedErrorMessage (moduleName, verificationErrorInfo).c_str ())
{
}