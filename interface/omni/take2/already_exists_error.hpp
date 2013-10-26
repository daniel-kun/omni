#ifndef OMNI_TAKE2_ALREADY_EXISTS_ERROR_HPP
#define OMNI_TAKE2_ALREADY_EXISTS_ERROR_HPP

#include <omni/take2/take2.hpp>
#include <omni/take2/domain.hpp>
#include <stdexcept>

#pragma warning(push)
#pragma warning(disable:4275)

namespace omni {
namespace take2 {

    class OMNI_TAKE2_API already_exists_error : public std::runtime_error {
    public:
        already_exists_error (domain domain, std::string const & identifier);
    };

} // namespace take2
} // namespace omni

#pragma warning(pop)

#endif // include guard
