#include <omni/core/do_while_statement.hpp>
#include <omni/core/block.hpp>
#include <omni/core/expression.hpp>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/NoFolder.h>

omni::core::do_while_statement::do_while_statement (std::shared_ptr <expression> condition, std::shared_ptr <block> body) :
    while_statement (condition, body)
{
}

llvm::BasicBlock * omni::core::do_while_statement::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    llvm::BasicBlock * whileBlock = getBody ()->llvmEmit (llvmBasicBlock->getContext (), std::string (), llvmBasicBlock->getParent ());
    llvm::BasicBlock * continueBlock = llvm::BasicBlock::Create (llvmBasicBlock->getContext (), "", llvmBasicBlock->getParent ());

    llvm::IRBuilder <true, llvm::NoFolder> builder (llvmBasicBlock);
    builder.CreateBr (whileBlock);

    llvm::IRBuilder <true, llvm::NoFolder> whileBuilder (whileBlock);
    whileBuilder.CreateCondBr (getCondition ()->llvmValue (whileBlock), whileBlock, continueBlock);

    return continueBlock;
}
