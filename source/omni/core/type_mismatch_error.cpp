#include <omni/core/type_mismatch_error.hpp>
#include <omni/core/type.hpp>

#include <sstream>

namespace {
/**
Builds and returns an error message that leftType is not equal to rightType.
**/
std::string buildTypeMismatchErrorMessage (omni::core::type & leftType, omni::core::type & rightType)
{
    std::stringstream result;
    result << "Type mismatch error: Type " << leftType.getName () << " does not equal Type " << rightType.getName ();
    return result.str ();
}
}

omni::core::type_mismatch_error::type_mismatch_error (omni::core::type & leftType, omni::core::type & rightType) :
    std::runtime_error (buildTypeMismatchErrorMessage (leftType, rightType).c_str ())
{

}
