#ifndef OMNI_CORE_VARIABLE_DECLARATION_EXPRESSION_HPP
#define OMNI_CORE_VARIABLE_DECLARATION_EXPRESSION_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/pure_expression.hpp>

namespace llvm {
    class Value;
}

namespace omni {
namespace core {
namespace model {
    class type;
    class expression;

    /**

    **/
    class OMNI_CORE_API variable_declaration_expression : public pure_expression {
    public:
        variable_declaration_expression ();
        variable_declaration_expression (std::shared_ptr <type> type);
        variable_declaration_expression (std::shared_ptr <expression> initializer);

        std::shared_ptr <type> getType () const override;
        void setType (std::shared_ptr <type> type);

        std::shared_ptr <expression> getInitializationExpression () const;
        void setInitializationExpression (std::shared_ptr <expression> initializer);

        llvm::Value * llvmPointerValue ();
        statement_emit_result llvmEmit (llvm::BasicBlock * llvmBasicBlock) override;

    private:
        std::shared_ptr <type> _type;
        llvm::Value * _llvmPointerValue; // Internal
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard                                             
