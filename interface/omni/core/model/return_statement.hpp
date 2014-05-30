#ifndef OMNI_CORE_RETURN_STATEMENT_HPP
#define OMNI_CORE_RETURN_STATEMENT_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/statement.hpp>

#include <memory>

namespace llvm {
    class BasicBlock;
}

namespace omni {
namespace core {
namespace model {
    class expression;

    class OMNI_CORE_API return_statement : public statement {
    public:
        return_statement ();
        return_statement (std::shared_ptr <expression> expression);

        std::shared_ptr <expression> getExpression ();
        const std::shared_ptr <expression> getExpression () const;
        void setExpression (std::shared_ptr <expression> expression);

        statement_emit_result llvmEmit (llvm::BasicBlock * llvmBasicBlock);
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
