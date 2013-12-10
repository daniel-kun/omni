#ifndef OMNI_CORE_EXPRESSION_STATEMENT_HPP
#define OMNI_CORE_EXPRESSION_STATEMENT_HPP

#include <omni/core/core.hpp>
#include <omni/core/statement.hpp>
#include <memory>

namespace llvm {
    class BasicBlock;
}

namespace omni {
namespace core {
    class expression;

    /**
    An expression_statement is a statement that executes an expression, but discards the result.
    **/
    class OMNI_CORE_API expression_statement : public statement {
    public:
        expression_statement (std::shared_ptr <expression> expression);
        
        void llvmEmit (llvm::BasicBlock * llvmBasicBlock) override;
        const std::shared_ptr <expression> & getExpression () const;

    private:
        std::shared_ptr <expression> _expression;
    };

} // namespace core
} // namespace omni

#endif // include guard
