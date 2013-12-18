#ifndef OMNI_CORE_USE_BEFORE_DECLARATION_ERROR_HPP
#define OMNI_CORE_USE_BEFORE_DECLARATION_ERROR_HPP

#include <omni/core/core.hpp>
#include <omni/core/domain.hpp>

#include <stdexcept>

#pragma warning(push)
#pragma warning(disable:4275)

namespace omni {
namespace core {

    /**
    Is thrown when something was used, before it was declared.
    E.g. when trying to take a value from a variable_declaration_statement, when that variable_declaration_statement was not executed (aka emitted) before.
    **/
    class OMNI_CORE_API use_before_declaration_error : public std::runtime_error {
    public:
        use_before_declaration_error (domain domain, std::string const & identifier);
    };

} // namespace core
} // namespace omni

#pragma warning(pop)

#endif // include guard
