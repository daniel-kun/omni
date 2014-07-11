#ifndef OMNI_CORE_MODEL_BUILTIN_LITERAL_HPP
#define OMNI_CORE_MODEL_BUILTIN_LITERAL_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/literal.hpp>
#include <omni/core/model/native_type_to_type_class.hpp>
#include <omni/core/not_implemented_error.hpp>

#include <memory>

namespace omni {
namespace core {
namespace model {

    /**
    @class builtin_literal builtin_literal.hpp omni/core/model/builtin_literal.hpp
    @brief A builtin_literal can be used to define literals of builtin numeric types (char, short, int, double, float).

    To access the value of a literal e.g. as a function parameter or in an assignment or similar, instantiate a literal_expression
    with this literal.
    **/
    template <typename T>
    class OMNI_CORE_API builtin_literal : public literal {
    public:
        explicit builtin_literal (context & context, T value);

        domain getDomain () const override;

        static const type_class typeClass = native_type_to_type_class <T>::typeClass;

        virtual llvm::Value * llvmValue ();

    private:
        T _value;
    };
} // namespace model
} // namespace core
} // namespace omni

#ifndef _MSC_VER

extern template class omni::core::model::builtin_literal <bool>;
extern template class omni::core::model::builtin_literal <char>;
extern template class omni::core::model::builtin_literal <signed char>;
extern template class omni::core::model::builtin_literal <unsigned char>;
extern template class omni::core::model::builtin_literal <signed short>;
extern template class omni::core::model::builtin_literal <unsigned short>;
extern template class omni::core::model::builtin_literal <signed int>;
extern template class omni::core::model::builtin_literal <unsigned int>;
extern template class omni::core::model::builtin_literal <signed long>;
extern template class omni::core::model::builtin_literal <unsigned long>;
extern template class omni::core::model::builtin_literal <signed long long>;
extern template class omni::core::model::builtin_literal <unsigned long long>;

#endif

#endif
