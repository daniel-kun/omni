#ifndef OMNI_CORE_VARIABLE_EXPRESSION_HPP
#define OMNI_CORE_VARIABLE_EXPRESSION_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/pure_expression.hpp>

#include <memory>

namespace omni {
namespace core {
namespace model {
    class variable_declaration_expression;

    /**
    A `variable expression' is any mention of a variable that is used to take that variable's value.
    E.g. in "int foo = x;", the "x" is a variable_expression.
    To assign values to a variable, use the variable_assignment_expression.
    **/
    class OMNI_CORE_API variable_expression : public pure_expression {
    public:
        variable_expression (std::shared_ptr <variable_declaration_expression> variable);

        static meta_info & getStaticMetaInfo ();

        meta_info & getMetaInfo () const override;

        domain getDomain () const override;

        std::shared_ptr <type> getType () const override;

        void setVariable (std::shared_ptr <variable_declaration_expression> variable);
        const std::shared_ptr <variable_declaration_expression> getVariable () const ;

        statement_emit_result llvmEmit (llvm::BasicBlock * llvmBasicBlock) override;

    private:
        std::shared_ptr <variable_declaration_expression> _variable;
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
