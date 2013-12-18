#include <omni/core/already_exists_error.hpp>
#include <sstream>

namespace {
std::string buildAlreadyExistsErrorMessage (omni::core::domain domain, std::string const & identifier)
{
    std::stringstream result;
    switch (domain) {
    case omni::core::domain::function:
        result << "The function \"" << identifier << "\" already exists.";
        break;
    default:
        result << "The identifier \"" << identifier << "\" already exists.";
        break;
    }
    return result.str ();
}
}

omni::core::already_exists_error::already_exists_error (omni::core::domain domain, std::string const & identifier) :
    std::runtime_error (buildAlreadyExistsErrorMessage (domain, identifier).c_str ())
{
}
