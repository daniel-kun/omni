#include <omni/core/model/native_type_to_type_class.hpp>
#include <omni/core/model/type_class.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(nativeTypeToTypeClassTests)

BOOST_AUTO_TEST_CASE (all)
{
    using namespace omni::core::model;

    static_assert (native_type_to_type_class <void>::typeClass == type_class::t_void, "void != t_void");
    static_assert (native_type_to_type_class <bool>::typeClass == type_class::t_boolean, "bool != t_boolean");
    static_assert (native_type_to_type_class <unsigned char>::typeClass == type_class::t_unsignedByte, "unsigned char != t_unsignedByte");
    static_assert (native_type_to_type_class <signed char>::typeClass == type_class::t_signedByte, "signed char != t_signedByte");
    static_assert (native_type_to_type_class <unsigned short>::typeClass == type_class::t_unsignedShort, "unsigned short != t_unsignedShort");
    static_assert (native_type_to_type_class <signed short>::typeClass == type_class::t_signedShort, "signed short != t_signedShort");
    static_assert (native_type_to_type_class <unsigned int>::typeClass == type_class::t_unsignedInt, "unsigned int != t_unsignedInt");
    static_assert (native_type_to_type_class <signed int>::typeClass == type_class::t_signedInt, "signed int != t_signedInt");
    static_assert (native_type_to_type_class <unsigned long>::typeClass == type_class::t_unsignedLong, "unsigned long != t_unsignedLong");
    static_assert (native_type_to_type_class <signed long>::typeClass == type_class::t_signedLong, "signed long != t_signedLong");
    static_assert (native_type_to_type_class <unsigned long long>::typeClass == type_class::t_unsignedLongLong, "unsigned long long != t_unsignedLongLong");
    static_assert (native_type_to_type_class <signed long long>::typeClass == type_class::t_signedLongLong, "signed long long != t_signedLongLong");
    static_assert (native_type_to_type_class <char>::typeClass == type_class::t_char, "char != t_char");
    static_assert (native_type_to_type_class <std::string>::typeClass == type_class::t_string, "std::string != t_string");
}

BOOST_AUTO_TEST_SUITE_END ()
