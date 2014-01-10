#ifndef OMNI_CORE_STATEMENT_EMIT_RESULT_HPP
#define OMNI_CORE_STATEMENT_EMIT_RESULT_HPP

#include <omni/core/core.hpp>

#include <memory>

namespace llvm {
    class BasicBlock;
    class Value;
}

namespace omni {
namespace core {

    /**
    statement_emit_result is a small helper-class intended to carry the information that is returned from a call to
    omni::core::statement::llmEmit().
    **/
    class OMNI_CORE_API statement_emit_result {
    public:
        statement_emit_result (llvm::BasicBlock * continueBlock, llvm::Value * value);

        llvm::BasicBlock * getContinueBlock () const;
        llvm::Value * getValue () const;
        bool hasValue () const;

    private:
        llvm::BasicBlock * _continueBlock;
        llvm::Value * _value;
    };
}
}

#endif // include guard
