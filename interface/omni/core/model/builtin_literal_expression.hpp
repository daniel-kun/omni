#ifndef OMNI_CORE_MODEL_BUILTIN_LITERAL_EXPRESSION_HPP
#define OMNI_CORE_MODEL_BUILTIN_LITERAL_EXPRESSION_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/literal_expression.hpp>
#include <omni/core/model/native_type_to_type_class.hpp>

namespace omni {
namespace core {
namespace model {

    /**
    @class builtin_literal_expression builtin_literal_expression.hpp omni/core/model/builtin_literal_expression.hpp
    @brief A builtin_literal_expression can be used to define literals of builtin numeric types (char, short, int, double, float).

    To access the value of a literal e.g. as a function parameter or in an assignment or similar, instantiate a literal_expression
    with this literal.
    **/
    template <typename T>
    class OMNI_CORE_API builtin_literal_expression : public literal_expression {
    public:
        explicit builtin_literal_expression (context & context, T value);

        static meta_info & getStaticMetaInfo ();

        virtual meta_info & getMetaInfo () const;

        std::string toString (bool fullyQualified = true) const override;

        domain getDomain () const override;
        std::shared_ptr <type> getType () const override;

        static const type_class typeClass = native_type_to_type_class <T>::typeClass;

        void setValue (T value);
        T getValue () const;

        statement_emit_result llvmEmit (llvm::BasicBlock * llvmBasicBlock) override;

    private:
        std::shared_ptr <type> _type;
        T _value;
    };
} // namespace model
} // namespace core
} // namespace omni

#ifndef _MSC_VER

extern template class omni::core::model::builtin_literal_expression <bool>;
extern template class omni::core::model::builtin_literal_expression <char>;
extern template class omni::core::model::builtin_literal_expression <signed char>;
extern template class omni::core::model::builtin_literal_expression <unsigned char>;
extern template class omni::core::model::builtin_literal_expression <signed short>;
extern template class omni::core::model::builtin_literal_expression <unsigned short>;
extern template class omni::core::model::builtin_literal_expression <signed int>;
extern template class omni::core::model::builtin_literal_expression <unsigned int>;
extern template class omni::core::model::builtin_literal_expression <signed long>;
extern template class omni::core::model::builtin_literal_expression <unsigned long>;
extern template class omni::core::model::builtin_literal_expression <signed long long>;
extern template class omni::core::model::builtin_literal_expression <unsigned long long>;

#endif

#endif
