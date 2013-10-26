#include <omni/take2/already_exists_error.hpp>

omni::take2::already_exists_error::already_exists_error (omni::take2::domain domain, std::string const & identifier) :
    std::runtime_error ("The identifier  already exists")
{
}
