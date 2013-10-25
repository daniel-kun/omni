#include <omni/take2/not_implemented_error.hpp>

omni::take2::not_implemented_error::not_implemented_error (std::string const & fileName, std::string const & functionName, int lineNumber) :
    std::logic_error ("Function " + functionName + " in file " + fileName + " not (fully) implemented!")
{
}
