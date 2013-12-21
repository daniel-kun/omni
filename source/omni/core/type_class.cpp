#include <omni/core/type_class.hpp>
#include <omni/core/not_implemented_error.hpp>

std::ostream & operator << (std::ostream & lhs, const omni::core::type_class rhs)
{
    using namespace omni::core;

    switch (rhs) {
    case omni::core::type_class::t_void:
        lhs << "t_void";
        break;
    case omni::core::type_class::t_boolean:
        lhs << "t_boolean";
        break;
    case omni::core::type_class::t_unsignedByte:
        lhs << "t_unsignedByte";
        break;
    case omni::core::type_class::t_signedByte:
        lhs << "t_signedByte";
        break;
    case omni::core::type_class::t_unsignedShort:
        lhs << "t_unsignedShort";
        break;
    case omni::core::type_class::t_signedShort:
        lhs << "t_signedShort";
        break;
    case omni::core::type_class::t_unsignedInt:
        lhs << "t_unsignedInt";
        break;
    case omni::core::type_class::t_signedInt:
        lhs << "t_signedInt";
        break;
    case omni::core::type_class::t_unsignedLong:
        lhs << "t_unsignedLong";
        break;
    case omni::core::type_class::t_signedLong:
        lhs << "t_signedLong";
        break;
    case omni::core::type_class::t_unsignedLongLong:
        lhs << "t_unsignedLongLong";
        break;
    case omni::core::type_class::t_signedLongLong:
        lhs << "t_signedLongLong";
        break;
    case omni::core::type_class::t_char:
        lhs << "t_char";
        break;
    case omni::core::type_class::t_string:
        lhs << "t_string";
        break;
    case omni::core::type_class::t_class:
        lhs << "t_class";
        break;
    case omni::core::type_class::t_enum:
        lhs << "t_enum";
        break;
    default:
        throw not_implemented_error (__FILE__, __FUNCTION__, __LINE__);
    }
    return lhs;
}
