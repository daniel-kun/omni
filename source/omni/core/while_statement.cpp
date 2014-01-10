#include <omni/core/while_statement.hpp>
#include <omni/core/expression.hpp>
#include <omni/core/block.hpp>

#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/NoFolder.h>

/**
Initializes this while_statement with the given condition and the given body.
This while_statement will repeatedly execute the given body while the given condition is true.
**/
omni::core::while_statement::while_statement (std::shared_ptr <expression> condition, std::shared_ptr <block> body) :
    _condition (condition),
    _body (body)
{
}

/**
Returns the condition on which the while_statement keeps repeating it's body.
**/
std::shared_ptr <omni::core::expression> omni::core::while_statement::getCondition ()
{
    return _condition;
}

/**
Returns the condition on which the while_statement keeps repeating it's body.
**/
const std::shared_ptr <omni::core::expression> omni::core::while_statement::getCondition () const
{
    return _condition;
}

/**
Returns the body that is being repeated by this whil_statement while the condition is true.
**/
std::shared_ptr <omni::core::block> omni::core::while_statement::getBody ()
{
    return _body;
}

/**
Returns the body that is being repeated by this whil_statement while the condition is true.
**/
const std::shared_ptr <omni::core::block> omni::core::while_statement::getBody () const
{
    return _body;
}

omni::core::statement_emit_result omni::core::while_statement::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    auto whileBlock = llvm::BasicBlock::Create (llvmBasicBlock->getContext (), "", llvmBasicBlock->getParent ());
    auto whileBodyBlock = _body->llvmEmit (llvmBasicBlock->getContext (), "", llvmBasicBlock->getParent ());
    auto continueBlock = llvm::BasicBlock::Create (llvmBasicBlock->getContext (), "", llvmBasicBlock->getParent ());

    // First, jump to the while block
    llvm::IRBuilder <true, llvm::NoFolder> builder (llvmBasicBlock);
    builder.CreateBr (whileBlock);

    llvm::IRBuilder <true, llvm::NoFolder> whileBuilder (whileBlock);
    whileBuilder.CreateCondBr (_condition->llvmEmit (whileBlock).getValue (), whileBodyBlock, continueBlock);

    llvm::IRBuilder <true, llvm::NoFolder> whileBodyBuilder (whileBodyBlock);
    whileBodyBuilder.CreateBr (whileBlock);

    return statement_emit_result (continueBlock, nullptr);
}
