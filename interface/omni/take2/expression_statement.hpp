#ifndef OMNI_TAKE2_EXPRESSION_STATEMENT_HPP
#define OMNI_TAKE2_EXPRESSION_STATEMENT_HPP

#include <omni/take2/take2.hpp>
#include <omni/take2/statement.hpp>
#include <memory>

namespace llvm {
    class BasicBlock;
}

namespace omni {
namespace take2 {
    class expression;

    /**
    An expression_statement is a statement that executes an expression, but discards the result.
    **/
    class OMNI_TAKE2_API expression_statement : public statement {
    public:
        expression_statement (std::shared_ptr <expression> expression);
        
        void llvmEmit (llvm::BasicBlock * llvmBasicBlock) override;
        const std::shared_ptr <expression> & getExpression () const;

    private:
        std::shared_ptr <expression> _expression;
    };

} // namespace take2
} // namespace omni

#endif // include guard
