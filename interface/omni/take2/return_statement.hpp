#ifndef OMNI_TAKE2_RETURN_STATEMENT_HPP
#define OMNI_TAKE2_RETURN_STATEMENT_HPP

#include <omni/take2/take2.hpp>
#include <omni/take2/statement.hpp>
#include <memory>

namespace llvm {
    class BasicBlock;
}

namespace omni {
namespace take2 {
    class expression;

    class OMNI_TAKE2_API return_statement : public statement {
    public:
        return_statement ();
        return_statement (std::shared_ptr <expression> expression);

        void llvmEmit (llvm::BasicBlock * llvmBasicBlock);
    private:
        std::shared_ptr <expression> _expression;
    };

} // namespace take2
} // namespace omni

#endif // include guard
