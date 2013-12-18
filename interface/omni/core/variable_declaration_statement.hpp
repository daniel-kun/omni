#ifndef OMNI_CORE_VARIABLE_DECLARATION_STATEMENT_HPP
#define OMNI_CORE_VARIABLE_DECLARATION_STATEMENT_HPP

#include <omni/core/core.hpp>
#include <omni/core/statement.hpp>

namespace llvm {
    class Value;
}

namespace omni {
namespace core {
    class type;
    class expression;

    /**

    **/
    class OMNI_CORE_API variable_declaration_statement : public statement {
    public:
        variable_declaration_statement (std::shared_ptr <type> variableType);
        variable_declaration_statement (std::shared_ptr <expression> initializationExpression);

        std::shared_ptr <type> getVariableType () const;
        std::shared_ptr <expression> getInitializationExpression () const;

        llvm::Value * llvmPointerValue ();
        void llvmEmit (llvm::BasicBlock * llvmBasicBlock) override;

    private:
        std::shared_ptr <type> _variableType;
        std::shared_ptr <expression> _initializationExpression; // Can be nullptr
        llvm::Value * _llvmPointerValue; // Internal
    };

} // namespace core
} // namespace omni

#endif // include guard
