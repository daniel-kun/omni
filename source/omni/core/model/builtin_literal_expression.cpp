#include <omni/core/model/builtin_literal_expression.hpp>
#include <omni/core/context.hpp>
#include <omni/core/model/type.hpp>
#include <omni/core/model/type_mismatch_error.hpp>

#include <llvm/IR/Constants.h>

#include <sstream>

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
@brief Initializes this builtin_literal_expression in the given context with the given value.

A builtin_literal_expression can only exist with a context, since the context defines how the given type is stored and how it behaves.
@param context The context that this builtin_literal_expression can be used in.
@param value The value that this builtin_literal_expression will emit.
**/
template <typename T>
omni::core::model::builtin_literal_expression <T>::builtin_literal_expression (context & context, T value) :
    _type (type::sharedBasicType (context, native_type_to_type_class <T>::typeClass)),
    _value (value)
{
}

template <typename T>
std::string omni::core::model::builtin_literal_expression <T>::toString (bool fullyQualified) const
{
    std::stringstream str;
    str << _value;
    if (fullyQualified) {
        str << getType ()->toString (false);
    }
    return str.str ();
}

template <typename T>
omni::core::domain omni::core::model::builtin_literal_expression <T>::getDomain () const
{
    return domain::builtin_literal_expression;
}

template <typename T>
std::shared_ptr <omni::core::model::type> omni::core::model::builtin_literal_expression <T>::getType () const
{
    return _type;
}
 
/**
@brief Changes the value of this builtin_literal to `value'.

Emits the signal ValueChanged.
@param value The new value for this builtin_literal
**/
template <typename T>
void omni::core::model::builtin_literal_expression <T>::setValue (T value)
{
    T oldValue = _value;
    _value = value;
    valueChanged (oldValue, _value);
}

/**
@brief Returns the current value for this builtin_literal.

@return Te current value for this builtin_literal.
**/
template <typename T>
T omni::core::model::builtin_literal_expression <T>::getValue () const
{
    return _value;
}

template <typename T>
omni::core::statement_emit_result omni::core::model::builtin_literal_expression <T>::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    if (native_type_to_type_class<T>::typeClass != getType ()->getTypeClass ()) {
        throw type_mismatch_error (* getType ()->getContext ()->sharedBasicType (native_type_to_type_class<T>::typeClass), * getType ());
    }
    return statement_emit_result (
            llvmBasicBlock,
            value_provider <T>::provideValue (getType ()->llvmType (), _value));
}

// We have explicit template instantiations for all supported types.
// That way, we do not need to define everything in the header file.

template class omni::core::model::builtin_literal_expression <bool>;
template class omni::core::model::builtin_literal_expression <char>;
template class omni::core::model::builtin_literal_expression <signed char>;
template class omni::core::model::builtin_literal_expression <unsigned char>;
template class omni::core::model::builtin_literal_expression <signed short>;
template class omni::core::model::builtin_literal_expression <unsigned short>;
template class omni::core::model::builtin_literal_expression <signed int>;
template class omni::core::model::builtin_literal_expression <unsigned int>;
template class omni::core::model::builtin_literal_expression <signed long>;
template class omni::core::model::builtin_literal_expression <unsigned long>;
template class omni::core::model::builtin_literal_expression <signed long long>;
template class omni::core::model::builtin_literal_expression <unsigned long long>;

