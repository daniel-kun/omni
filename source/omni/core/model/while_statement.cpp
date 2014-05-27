#include <omni/core/model/while_statement.hpp>
#include <omni/core/model/expression.hpp>
#include <omni/core/model/block.hpp>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/NoFolder.h>

/**
Initializes this while_statement with the given condition and the given body.
This while_statement will repeatedly execute the given body while the given condition is true.
**/
omni::core::model::while_statement::while_statement (omni::core::model::scope & parent) :
    statement (parent),
    _condition (),
    _body ()
{
}

/**
Returns the condition on which the while_statement keeps repeating it's body.
**/
std::shared_ptr <omni::core::model::expression> omni::core::model::while_statement::getCondition ()
{
    return _condition;
}

/**
Returns the condition on which the while_statement keeps repeating it's body.
**/
const std::shared_ptr <omni::core::model::expression> omni::core::model::while_statement::getCondition () const
{
    return _condition;
}

void omni::core::model::while_statement::setCondition (std::shared_ptr <omni::core::model::expression> condition)
{
    _condition = condition;
}


/**
Returns the body that is being repeated by this whil_statement while the condition is true.
**/
std::shared_ptr <omni::core::model::block> omni::core::model::while_statement::getBody ()
{
    return _body;
}

/**
Returns the body that is being repeated by this whil_statement while the condition is true.
**/
const std::shared_ptr <omni::core::model::block> omni::core::model::while_statement::getBody () const
{
    return _body;
}

void omni::core::model::while_statement::setBody (std::shared_ptr <omni::core::model::block> body)
{
    _body = body;
}

omni::core::statement_emit_result omni::core::model::while_statement::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    auto whileBlock = llvm::BasicBlock::Create (llvmBasicBlock->getContext (), "", llvmBasicBlock->getParent ());
    auto whileBodyBlock = _body->llvmEmit (llvmBasicBlock);
    auto continueBlock = llvm::BasicBlock::Create (llvmBasicBlock->getContext (), "", llvmBasicBlock->getParent ());

    // First, jump to the while block
    llvm::IRBuilder <true, llvm::NoFolder> builder (llvmBasicBlock);
    builder.CreateBr (whileBlock);

    llvm::IRBuilder <true, llvm::NoFolder> whileBuilder (whileBlock);
    whileBuilder.CreateCondBr (_condition->llvmEmit (whileBlock).getValue (), whileBodyBlock.getContinueBlock (), continueBlock);

    llvm::IRBuilder <true, llvm::NoFolder> whileBodyBuilder (whileBodyBlock.getContinueBlock ());
    whileBodyBuilder.CreateBr (whileBlock);

    return statement_emit_result (continueBlock, nullptr);
}
