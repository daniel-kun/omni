#include <omni/core/while_statement.hpp>
#include <omni/core/expression.hpp>
#include <omni/core/block.hpp>

#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/NoFolder.h>

omni::core::while_statement::while_statement (std::shared_ptr <expression> condition, std::shared_ptr <block> body) :
    _condition (condition),
    _body (body)
{
}

std::shared_ptr <omni::core::expression> omni::core::while_statement::getCondition ()
{
    return _condition;
}

const std::shared_ptr <omni::core::expression> omni::core::while_statement::getCondition () const
{
    return _condition;
}

std::shared_ptr <omni::core::block> omni::core::while_statement::getBody ()
{
    return _body;
}

const std::shared_ptr <omni::core::block> omni::core::while_statement::getBody () const
{
    return _body;
}

llvm::BasicBlock * omni::core::while_statement::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    auto whileBlock = llvm::BasicBlock::Create (llvmBasicBlock->getContext (), "", llvmBasicBlock->getParent ());
    auto whileBodyBlock = _body->llvmEmit (llvmBasicBlock->getContext (), "", llvmBasicBlock->getParent ());
    auto continueBlock = llvm::BasicBlock::Create (llvmBasicBlock->getContext (), "", llvmBasicBlock->getParent ());

    // First, jump to the while block
    llvm::IRBuilder <true, llvm::NoFolder> builder (llvmBasicBlock);
    builder.CreateBr (whileBlock);

    llvm::IRBuilder <true, llvm::NoFolder> whileBuilder (whileBlock);
    whileBuilder.CreateCondBr (_condition->llvmValue (whileBlock), whileBodyBlock, continueBlock);

    llvm::IRBuilder <true, llvm::NoFolder> whileBodyBuilder (whileBodyBlock);
    whileBodyBuilder.CreateBr (whileBlock);

    return continueBlock;
}
