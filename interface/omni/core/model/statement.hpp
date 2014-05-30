#ifndef OMNI_CORE_STATEMENT_HPP
#define OMNI_CORE_STATEMENT_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/scope.hpp>
#include <omni/core/statement_emit_result.hpp>

namespace llvm {
    class BasicBlock;
    class Value;
}

namespace omni {
namespace core {
namespace model {

    /**
    Abstract.
    A statement can be anything that is being executed in a block.
    There is a distinction between statements that return a result ("expressions") and all other statements that do not
    return a result. Everything that returns a result derives from omni::core::expression, while anything else does directly
    derive from omni::core::statement.
    **/
    class OMNI_CORE_API statement : public scope {
    public:
        statement ();
        virtual ~ statement ();

        virtual statement_emit_result llvmEmit (llvm::BasicBlock * llvmBasicBlock) = 0;
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
