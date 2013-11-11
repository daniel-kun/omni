#include <omni/take2/already_exists_error.hpp>
#include <sstream>

namespace {
std::string create_error_message (omni::take2::domain domain, std::string const & identifier)
{
    std::stringstream result;
    switch (domain) {
    case omni::take2::domain::function:
        result << "The function \"" << identifier << "\" already exists.";
        break;
    default:
        result << "The identifier \"" << identifier << "\" already exists.";
        break;
    }
    return result.str ();
}
}

omni::take2::already_exists_error::already_exists_error (omni::take2::domain domain, std::string const & identifier) :
    std::runtime_error (create_error_message (domain, identifier).c_str ())
{
}
