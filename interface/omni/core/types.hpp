#ifndef OMNI_CORE_TYPES_HPP
#define OMNI_CORE_TYPES_HPP

namespace omni {
namespace core {

/**
A list of all built-in types
**/
enum class types {
// custom class
Class,

// no type
Void,

// int types
Int,
Int8,
Int16,
Int32,
Int64,

//unsigned int types
UnsignedInt,
UnsignedInt8,
UnsignedInt16,
UnsignedInt32,
UnsignedInt64,

// short types
Short,
Short8,
Short16,

// unsigned short types
UnsignedShort,
UnsignedShort8,
UnsignedShort16,

// floating point types
Float,
Double,

// character types
Char,
UnsignedChar,
UnicodeChar,
};

} // namespace core
} // namespace omni

#endif // include guard
