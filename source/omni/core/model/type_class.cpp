#include <omni/core/model/type_class.hpp>
#include <omni/core/not_implemented_error.hpp>

std::ostream & omni::core::model::operator << (std::ostream & lhs, const omni::core::model::type_class rhs)
{
    using namespace omni::core::model;

    switch (rhs) {
    case type_class::t_void:
        lhs << "t_void";
        break;
    case type_class::t_boolean:
        lhs << "t_boolean";
        break;
    case type_class::t_unsignedByte:
        lhs << "t_unsignedByte";
        break;
    case type_class::t_signedByte:
        lhs << "t_signedByte";
        break;
    case type_class::t_unsignedShort:
        lhs << "t_unsignedShort";
        break;
    case type_class::t_signedShort:
        lhs << "t_signedShort";
        break;
    case type_class::t_unsignedInt:
        lhs << "t_unsignedInt";
        break;
    case type_class::t_signedInt:
        lhs << "t_signedInt";
        break;
    case type_class::t_unsignedLong:
        lhs << "t_unsignedLong";
        break;
    case type_class::t_signedLong:
        lhs << "t_signedLong";
        break;
    case type_class::t_unsignedLongLong:
        lhs << "t_unsignedLongLong";
        break;
    case type_class::t_signedLongLong:
        lhs << "t_signedLongLong";
        break;
    case type_class::t_char:
        lhs << "t_char";
        break;
    case type_class::t_string:
        lhs << "t_string";
        break;
    case type_class::t_class:
        lhs << "t_class";
        break;
    case type_class::t_enum:
        lhs << "t_enum";
        break;
    default:
        throw omni::core::not_implemented_error (__FILE__, __FUNCTION__, __LINE__);
    }
    return lhs;
}
