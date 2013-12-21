#ifndef OMNI_CORE_NATIVE_TYPE_TO_TYPE_CLASS_HPP
#define OMNI_CORE_NATIVE_TYPE_TO_TYPE_CLASS_HPP

#include <omni/core/core.hpp>
#include <omni/core/type_class.hpp>

#include <string>

namespace omni {
namespace core {

    /**
    Allows templated conversion from C++ native types to the corresponding type_class.
    Use it as this:
    type_class t = native_type_to_type_class <t>::typeClass;
    **/
    template <typename T>
    class native_type_to_type_class {
    };
}
}

// void -> t_void
template <>
class omni::core::native_type_to_type_class <void> {
public:
    typedef void nativeType;
    static const type_class typeClass = type_class::t_void;
};

// bool -> t_boolean
template <>
class omni::core::native_type_to_type_class <bool> {
public:
    typedef bool nativeType;
    static const type_class typeClass = type_class::t_boolean;
};

// unsigned char -> t_unsignedByte
template <>
class omni::core::native_type_to_type_class <unsigned char> {
public:
    typedef unsigned char nativeType;
    static const type_class typeClass = type_class::t_unsignedByte;
};

// signed char -> t_signedByte
template <>
class omni::core::native_type_to_type_class <signed char> {
public:
    typedef signed char nativeType;
    static const type_class typeClass = type_class::t_signedByte;
};

// unsigned short -> t_unsignedShort
template <>
class omni::core::native_type_to_type_class <unsigned short> {
public:
    typedef unsigned short nativeType;
    static const type_class typeClass = type_class::t_unsignedShort;
};

// signed short -> t_signedShort
template <>
class omni::core::native_type_to_type_class <signed short> {
public:
    typedef signed short nativeType;
    static const type_class typeClass = type_class::t_signedShort;
};

// unsigned int -> t_unsignedInt
template <>
class omni::core::native_type_to_type_class <unsigned int> {
public:
    typedef unsigned int nativeType;
    static const type_class typeClass = type_class::t_unsignedInt;
};

// signed int -> t_signedInt
template <>
class omni::core::native_type_to_type_class <signed int> {
public:
    typedef signed int nativeType;
    static const type_class typeClass = type_class::t_signedInt;
};

// unsigned long -> t_unsignedLong
template <>
class omni::core::native_type_to_type_class <unsigned long> {
public:
    typedef unsigned long nativeType;
    static const type_class typeClass = type_class::t_unsignedLong;
};

// signed long -> t_signedLong
template <>
class omni::core::native_type_to_type_class <signed long> {
public:
    typedef signed long nativeType;
    static const type_class typeClass = type_class::t_signedLong;
};

// unsigned long long -> t_unsignedLongLong
template <>
class omni::core::native_type_to_type_class <unsigned long long> {
public:
    typedef unsigned long long nativeType;
    static const type_class typeClass = type_class::t_unsignedLongLong;
};

// signed long long -> t_signedLongLong
template <>
class omni::core::native_type_to_type_class <signed long long> {
public:
    typedef signed long long nativeType;
    static const type_class typeClass = type_class::t_signedLongLong;
};

// char -> t_char
template <>
class omni::core::native_type_to_type_class <char> {
public:
    typedef char nativeType;
    static const type_class typeClass = type_class::t_char;
};

// std::string -> t_string
template <>
class omni::core::native_type_to_type_class <std::string> {
public:
    typedef std::string nativeType;
    static const type_class typeClass = type_class::t_string;
};

#endif
