#include <omni/core/return_statement.hpp>
#include <omni/core/expression.hpp>

#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/NoFolder.h>

omni::core::model::return_statement::return_statement () :
    _expression ()
{
}

omni::core::model::return_statement::return_statement (std::shared_ptr <expression> expression) :
    _expression (expression)
{
}

omni::core::statement_emit_result omni::core::model::return_statement::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    llvm::IRBuilder <true, llvm::NoFolder> builder (llvmBasicBlock);
    if (_expression.get () == nullptr) {
        builder.CreateRetVoid ();
    } else {
        builder.CreateRet (_expression->llvmEmit (llvmBasicBlock).getValue ());
    }
    return statement_emit_result (llvmBasicBlock, nullptr);
}
