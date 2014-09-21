#include <omni/core/invalid_argument_error.hpp>

#include <sstream>

namespace {
std::string buildErrorMessage (std::string const & fileName, std::string const & functionName, int lineNumber, std::string argumentName, std::string const & errorMessage)
{
    std::stringstream result;
    result << "Error at " << functionName << " in " << fileName << ":" << lineNumber << ": The argument \"" << argumentName << "\" has an invalid value (" << errorMessage << ")";
    return result.str ();
}
}

omni::core::invalid_argument_error::invalid_argument_error (
    std::string const & fileName,
    std::string const & functionName,
    int lineNumber,
    std::string argumentName,
    std::string const & errorMessage) :

    std::invalid_argument (buildErrorMessage (fileName, functionName, lineNumber, argumentName, errorMessage).c_str ())
{

}
