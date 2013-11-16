#include <omni/take2/builtin_literal.hpp>
#include <omni/take2/type_class.hpp>
#include <omni/take2/type.hpp>

template <>
omni::take2::builtin_literal <signed short>::builtin_literal (context & context, signed short value) :
    literal (static_cast <std::shared_ptr <type>> (new type (context, type_class::t_signedShort))),
    _value (value)
{
}

template <>
omni::take2::builtin_literal <unsigned short>::builtin_literal (context & context, unsigned short value) :
    literal (static_cast <std::shared_ptr <type>> (new type (context, type_class::t_unsignedShort))),
    _value (value)
{
}

template <>
omni::take2::builtin_literal <signed int>::builtin_literal (context & context, signed int value) :
    literal (static_cast <std::shared_ptr <type>> (new type (context, type_class::t_signedInt))),
    _value (value)
{
}

template <>
omni::take2::builtin_literal <unsigned int>::builtin_literal (context & context, unsigned int value) :
    literal (static_cast <std::shared_ptr <type>> (new type (context, type_class::t_unsignedInt))),
    _value (value)
{
}

//

template <>
llvm::Value * omni::take2::builtin_literal <signed short>::llvmValue ()
{
    switch (getType ()->getTypeClass ()) {
    case type_class::t_signedShort:
        return llvm::ConstantInt::get (getType ()->llvmType (), _value, true);
        break;
    default:
        throw not_implemented_error (__FILE__, __FUNCTION__, __LINE__);
    }
}

template <>
llvm::Value * omni::take2::builtin_literal <unsigned short>::llvmValue ()
{
    switch (getType ()->getTypeClass ()) {
    case type_class::t_unsignedShort:
        return llvm::ConstantInt::get (getType ()->llvmType (), _value, false);
        break;
    default:
        throw not_implemented_error (__FILE__, __FUNCTION__, __LINE__);
    }
}

template <>
llvm::Value * omni::take2::builtin_literal <signed int>::llvmValue ()
{
    switch (getType ()->getTypeClass ()) {
    case type_class::t_signedInt:
        return llvm::ConstantInt::get (getType ()->llvmType (), _value, true);
        break;
    default:
        throw not_implemented_error (__FILE__, __FUNCTION__, __LINE__);
    }
}

template <>
llvm::Value * omni::take2::builtin_literal <unsigned int>::llvmValue ()
{
    switch (getType ()->getTypeClass ()) {
    case type_class::t_unsignedInt:
        return llvm::ConstantInt::get (getType ()->llvmType (), _value, true);
        break;
    default:
        throw not_implemented_error (__FILE__, __FUNCTION__, __LINE__);
    }
}
