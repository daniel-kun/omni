#include <omni/core/model/do_while_statement.hpp>
#include <omni/core/model/block.hpp>
#include <omni/core/model/expression.hpp>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/NoFolder.h>

omni::core::model::do_while_statement::do_while_statement (std::shared_ptr <expression> condition, std::shared_ptr <block> body) :
    while_statement (condition, body)
{
}

omni::core::statement_emit_result omni::core::model::do_while_statement::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    llvm::BasicBlock * whileBlock = getBody ()->llvmEmit (llvmBasicBlock).getContinueBlock ();
    llvm::BasicBlock * continueBlock = llvm::BasicBlock::Create (llvmBasicBlock->getContext (), "", llvmBasicBlock->getParent ());

    llvm::IRBuilder <true, llvm::NoFolder> builder (llvmBasicBlock);
    builder.CreateBr (whileBlock);

    llvm::IRBuilder <true, llvm::NoFolder> whileBuilder (whileBlock);
    whileBuilder.CreateCondBr (getCondition ()->llvmEmit (whileBlock).getValue (), whileBlock, continueBlock);

    return statement_emit_result (continueBlock, nullptr);
}
