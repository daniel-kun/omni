#ifndef OMNI_CORE_VARIABLE_DECLARATION_EXPRESSION_HPP
#define OMNI_CORE_VARIABLE_DECLARATION_EXPRESSION_HPP

#include <omni/core/core.hpp>
#include <omni/core/pure_expression.hpp>

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
        variable_declaration_expression (std::shared_ptr <type> variableType);
        variable_declaration_expression (std::shared_ptr <expression> initializationExpression);

        std::shared_ptr <type> getType () const override;
        std::shared_ptr <expression> getInitializationExpression () const;

        llvm::Value * llvmPointerValue ();
        statement_emit_result llvmEmit (llvm::BasicBlock * llvmBasicBlock) override;

    private:
        std::shared_ptr <type> _type;
        std::shared_ptr <expression> _initializationExpression; // Can be nullptr
        llvm::Value * _llvmPointerValue; // Internal
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard                                             
