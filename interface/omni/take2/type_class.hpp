#ifndef OMNI_TAKE2_TYPE_CLASS_HPP
#define OMNI_TAKE2_TYPE_CLASS_HPP

#include <omni/take2/take2.hpp>

namespace omni {
namespace take2 {

    enum class type_class {
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

} // namespace take2
} // namespace omni

#endif // include guard
