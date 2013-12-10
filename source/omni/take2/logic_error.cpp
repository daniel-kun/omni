#include <omni/take2/logic_error.hpp>

#include <sstream>

namespace {
std::string buildErrorMessage (std::string const & fileName, std::string const & functionName, int lineNumber, std::string const & errorMessage)
{
    std::stringstream result;
    result << "Error at " << functionName << " in " << fileName << ":" << lineNumber << ": " << errorMessage;
    return result.str ();
}
}

omni::take2::logic_error::logic_error (std::string const & fileName, std::string const & functionName, int lineNumber, std::string const & errorMessage) :
    std::logic_error (buildErrorMessage (fileName, functionName, lineNumber, errorMessage).c_str ())
{

}
