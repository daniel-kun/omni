#ifndef OMNI_CORE_TYPE_CLASS_HPP
#define OMNI_CORE_TYPE_CLASS_HPP

#include <omni/core/core.hpp>
#include <ostream>

namespace omni {
namespace core {
namespace model {

    enum class type_class {
        t_void,
        t_boolean,
        t_unsignedByte,
        t_signedByte,
        t_unsignedShort,
        t_signedShort,
        t_unsignedInt,
        t_signedInt,
        t_unsignedLong,
        t_signedLong,
        t_unsignedLongLong,
        t_signedLongLong,
        t_char,
        t_string,
        t_class,
        t_enum
    };

    std::ostream OMNI_CORE_API & operator << (std::ostream & lhs, const omni::core::model::type_class rhs);

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
