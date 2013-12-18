#include <omni/core/no_context_error.hpp>
#include <sstream>

namespace {
std::string buildNoContextErrorMessage (omni::core::domain domain, std::string const & identifier)
{
    std::stringstream result;
    switch (domain) {
    case omni::core::domain::function:
        result << "The function \"" << identifier << "\" was not added to a context.";
        break;
    default:
        result << "The entity \"" << identifier << "\" was not added to a context.";
        break;
    }
    return result.str ();
}
}

omni::core::no_context_error::no_context_error (omni::core::domain domain, std::string const & identifier) :
    std::runtime_error (buildNoContextErrorMessage (domain, identifier).c_str ())
{
}
