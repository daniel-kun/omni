#ifndef OMNI_TAKE2_NOT_IMPLEMENTED_ERROR_HPP
#define OMNI_TAKE2_NOT_IMPLEMENTED_ERROR_HPP

#include <omni/take2/take2.hpp>
#include <omni/take2/logic_error.hpp>
#include <string>

#pragma warning(push)
#pragma warning(disable:4275)

namespace omni {
namespace take2 {

    class OMNI_TAKE2_API not_implemented_error : public omni::take2::logic_error {
    public:
        not_implemented_error (std::string const & fileName, std::string const & functionName, int lineNumber);
    };

} // namespace take2
} // namespace omni

#pragma warning(pop)

#endif // include guard
