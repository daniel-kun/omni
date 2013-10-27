#include <omni/take2/builtin_literal.hpp>
#include <omni/take2/type_class.hpp>
#include <omni/take2/type.hpp>

template <>
omni::take2::builtin_literal <signed int>::builtin_literal (context & context, int value) :
    literal (static_cast <std::shared_ptr <type>> (new type (context, type_class::t_signedInt))),
    _value (value)
{
}

template <>
llvm::Value * omni::take2::builtin_literal <signed int>::llvmValue ()
{
    switch (getType ()->getTypeClass ()) {
    case type_class::t_signedInt:
        return llvm::ConstantInt::get (getType ()->llvmType (), _value);
        break;
    default:
        throw not_implemented_error (__FILE__, __FUNCTION__, __LINE__);
    }
}
