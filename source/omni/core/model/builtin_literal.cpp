#include <omni/core/model/builtin_literal.hpp>
#include <omni/core/context.hpp>
#include <omni/core/model/type_class.hpp>
#include <omni/core/model/type.hpp>
#include <omni/core/model/type_mismatch_error.hpp>

#include <llvm/IR/Constants.h>

namespace {

/*
Helper base-class to provide signed values.
See the template specialisations of value_provider below, each picking the correct helper base-class.
*/
class signed_provider {
public:
    template <typename T>
    static llvm::Value * provideValue (llvm::Type * type, T value)
    {
        return llvm::ConstantInt::getSigned (type, value);
    }
};

/*
Helper base-class to provide unsigned values.
See the template specialisations of value_provider below, each picking the correct helper base-class.
*/
class unsigned_provider {
public:
    template <typename T>
    static llvm::Value * provideValue (llvm::Type * type, T value)
    {
        return llvm::ConstantInt::get (type, value);
    }
};

template <typename T> class value_provider {};

template <> class value_provider <bool> : public signed_provider { };
template <> class value_provider <char> : public signed_provider { };
template <> class value_provider <signed char> : public signed_provider { };
template <> class value_provider <unsigned char> : public unsigned_provider { };
template <> class value_provider <signed short> : public signed_provider { };
template <> class value_provider <unsigned short> : public unsigned_provider { };
template <> class value_provider <signed int> : public signed_provider { };
template <> class value_provider <unsigned int> : public unsigned_provider { };
template <> class value_provider <signed long> : public signed_provider { };
template <> class value_provider <unsigned long> : public unsigned_provider { };
template <> class value_provider <signed long long> : public signed_provider { };
template <> class value_provider <unsigned long long> : public unsigned_provider { };

}

/**
@brief Initializes this builtin_literal in the given context with the given value.

A builtin_literal can only exist with a context, since the context defines how the given type is stored and how it behaves.
@param context The context that this builtin_literal can be used in.
@param value The value that this builtin_literal will provide.
**/
template <typename T>
omni::core::model::builtin_literal <T>::builtin_literal (context & context, T value) :
    literal (type::sharedBasicType (context, native_type_to_type_class <T>::typeClass)),
    _value (value)
{
}

template <typename T>
omni::core::domain omni::core::model::builtin_literal <T>::getDomain () const
{
    return domain::builtin_literal;
}

/*
Internal.

Returns an llvm::Value that corresponds to the value of this builtin_literal.
*/
template <typename T>
llvm::Value * omni::core::model::builtin_literal <T>::llvmValue ()
{
    if (native_type_to_type_class<T>::typeClass != getType ()->getTypeClass ()) {
        throw type_mismatch_error (* getType ()->getContext ()->sharedBasicType (native_type_to_type_class<T>::typeClass), * getType ());
    }
    return value_provider <T>::provideValue (getType ()->llvmType (), _value);
}

// We have explicit template instantiations for all supported types.
// That way, we do not need to define everything in the header file.

template omni::core::model::builtin_literal <bool>;
template omni::core::model::builtin_literal <char>;
template omni::core::model::builtin_literal <signed char>;
template omni::core::model::builtin_literal <unsigned char>;
template omni::core::model::builtin_literal <signed short>;
template omni::core::model::builtin_literal <unsigned short>;
template omni::core::model::builtin_literal <signed int>;
template omni::core::model::builtin_literal <unsigned int>;
template omni::core::model::builtin_literal <signed long>;
template omni::core::model::builtin_literal <unsigned long>;
template omni::core::model::builtin_literal <signed long long>;
template omni::core::model::builtin_literal <unsigned long long>;
