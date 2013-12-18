#ifndef OMNI_CORE_TYPE_MISMATCH_ERROR_HPP
#define OMNI_CORE_TYPE_MISMATCH_ERROR_HPP

#include <omni/core/core.hpp>
#include <omni/core/domain.hpp>

#include <stdexcept>

#pragma warning(push)
#pragma warning(disable:4275)

namespace omni {
namespace core {
    class type;

    /**
    Is thrown when something expected two types to match exactly, but they did not match.
    E.g. binary_operator_expression's ctor expects the types of the left and right hand side expressions to return the same type.
    Same for variable assignments, etc.
    **/
    class OMNI_CORE_API type_mismatch_error : public std::runtime_error {
    public:
        type_mismatch_error (type & leftType, type & rightType);
    };

} // namespace core
} // namespace omni

#pragma warning(pop)

#endif // include guard
