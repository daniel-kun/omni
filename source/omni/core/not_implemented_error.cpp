#include <omni/core/not_implemented_error.hpp>

omni::core::not_implemented_error::not_implemented_error (std::string const & fileName, std::string const & functionName, int lineNumber) :
    omni::core::logic_error (functionName, fileName, lineNumber, "Function is not (fully) implemented")
{
}
