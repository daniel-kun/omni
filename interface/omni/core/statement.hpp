#ifndef OMNI_CORE_STATEMENT_HPP
#define OMNI_CORE_STATEMENT_HPP

#include <omni/core/core.hpp>
#include <omni/core/context_part.hpp>

namespace llvm {
    class BasicBlock;
}

namespace omni {
namespace core {

    /**
    A statement can be anything that is being executed in a block. Statements do not have results. In contrast,
    expressions have results, that's why an expression can be a statement. In that case, the result is discarded.
    @see expression_statement.
    **/
    class OMNI_CORE_API statement : public context_part {
    public:
        virtual ~ statement ();
        virtual void llvmEmit (llvm::BasicBlock * llvmBasicBlock) = 0;
    };

} // namespace core
} // namespace omni

#endif // include guard
