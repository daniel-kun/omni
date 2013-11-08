#ifndef OMNI_TAKE2_LOGIC_ERROR_HPP
#define OMNI_TAKE2_LOGIC_ERROR_HPP

#include <omni/take2/take2.hpp>
#include <stdexcept>
#include <string>

#pragma warning(push)
#pragma warning(disable:4275)

namespace omni {
namespace take2 {

    class OMNI_TAKE2_API logic_error : public std::logic_error {
    public:
        logic_error (std::string const & fileName, std::string const & functionName, int lineNumber, std::string const & errorMessage);
    };

} // namespace take2
} // namespace omni

#pragma warning(pop)

#endif // include guard
