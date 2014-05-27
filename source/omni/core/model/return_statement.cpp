#include <omni/core/model/return_statement.hpp>
#include <omni/core/model/expression.hpp>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/NoFolder.h>

omni::core::model::return_statement::return_statement (omni::core::model::scope & parent) :
    statement (parent),
    _expression ()
{
}

omni::core::model::return_statement::return_statement (omni::core::model::scope & parent, std::shared_ptr <expression> expression) :
    statement (parent),
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
