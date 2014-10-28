#include <omni/core/model/if_statement.hpp>
#include <omni/core/context.hpp>
#include <omni/core/model/expression.hpp>
#include <omni/core/model/block.hpp>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/NoFolder.h>

// See meta_info.cpp for initialization.
namespace omniMetaImpl {
extern omni::core::model::meta_info if_statementMetaInfo;
}

/**
Initializes this if_statement with the given condition and the given true- and elseBlocks.
@param condition The condition depending on which either the trueBlock or the elseBlock will be executed. The condition must be provided.
@param trueBlock The block that will be executed when the condition is true. The trueBlock must be provided.
@param elseBlock The block that will be executed when the condition is false. The elseBlock is optional and can be nullptr.
**/
omni::core::model::if_statement::if_statement (std::shared_ptr <expression> condition,
                                               std::shared_ptr <block> trueBlock,
                                               std::shared_ptr <block> elseBlock) :
    statement ()
{
    setCondition (condition);
    setTrueBlock (trueBlock);
    setElseBlock (elseBlock);
}

omni::core::model::meta_info & omni::core::model::if_statement::getStaticMetaInfo ()
{
    return omniMetaImpl::if_statementMetaInfo;
}

omni::core::model::meta_info & omni::core::model::if_statement::getMetaInfo () const
{
    return getStaticMetaInfo ();
}

omni::core::domain omni::core::model::if_statement::getDomain () const
{
    return domain::if_statement;
}

void omni::core::model::if_statement::setCondition (std::shared_ptr <omni::core::model::expression> condition)
{
    setComponent (domain::expression, "condition", condition);
}

/**
@return Returns the condition depending on which either the trueBlock or the elseBlock will be excuted.
**/
std::shared_ptr <omni::core::model::expression> omni::core::model::if_statement::getCondition ()
{
    return getComponentAs <expression> (domain::expression, "condition");
}

/**
@return Returns the condition depending on which either the trueBlock or the elseBlock will be excuted.
**/
const std::shared_ptr <omni::core::model::expression> omni::core::model::if_statement::getCondition () const
{
    return getComponentAs <expression> (domain::expression, "condition");
}

void omni::core::model::if_statement::setTrueBlock (std::shared_ptr <omni::core::model::block> trueBlock)
{
    setComponent (domain::block, "trueBlock", trueBlock);
}

/**
@return Returns the block that will be execute when the condition is true. Is never nullptr.
**/
std::shared_ptr <omni::core::model::block> omni::core::model::if_statement::getTrueBlock ()
{
    return getComponentAs <block> (domain::block, "trueBlock");
}

/**
@return Returns the block that will be execute when the condition is true. Is never nullptr.
**/
const std::shared_ptr <omni::core::model::block> omni::core::model::if_statement::getTrueBlock () const
{
    return getComponentAs <block> (domain::block, "trueBlock");
}

void omni::core::model::if_statement::setElseBlock (std::shared_ptr <omni::core::model::block> elseBlock)
{
    setComponent (domain::block, "elseBlock", elseBlock);
}

/**
@return Returns the block that will be execute when the condition is false. Can be nullptr.
**/
std::shared_ptr <omni::core::model::block> omni::core::model::if_statement::getElseBlock ()
{
    return getComponentAs <block> (domain::block, "elseBlock");
}

/**
@return Returns the block that will be execute when the condition is false. Can be nullptr.
**/
const std::shared_ptr <omni::core::model::block> omni::core::model::if_statement::getElseBlock () const
{
    return getComponentAs <block> (domain::block, "elseBlock");
}

/**
@internal
**/
omni::core::statement_emit_result omni::core::model::if_statement::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    llvm::BasicBlock * llvmTrueBlock = getTrueBlock ()->llvmEmit (llvmBasicBlock).getContinueBlock ();
    llvm::BasicBlock * llvmFalseBlock = nullptr;

    bool terminatorNeeded = false;

    std::shared_ptr <block> elseBlock = getElseBlock ();
    if (elseBlock != nullptr) {
        llvmFalseBlock = elseBlock->llvmEmit (llvmBasicBlock).getContinueBlock ();
        if (llvmFalseBlock->getTerminator () == nullptr) {
            terminatorNeeded = true;
        }
    }

    if (llvmTrueBlock->getTerminator () == nullptr) {
        terminatorNeeded = true;
    }

    llvm::BasicBlock * result = llvmBasicBlock;
    if (terminatorNeeded) {
        result = llvm::BasicBlock::Create (llvmBasicBlock->getContext (), "", llvmBasicBlock->getParent ());

        if (llvmTrueBlock->getTerminator () == nullptr) {
            llvm::IRBuilder <true, llvm::NoFolder> builder (llvmTrueBlock);
            builder.CreateBr (result);
        }

        if (llvmFalseBlock != nullptr && llvmFalseBlock->getTerminator () == nullptr) {
            llvm::IRBuilder <true, llvm::NoFolder> builder (llvmFalseBlock);
            builder.CreateBr (result);
        }
    }

    llvm::IRBuilder <true, llvm::NoFolder> builder (llvmBasicBlock);
    builder.CreateCondBr (getCondition ()->llvmEmit (llvmBasicBlock).getValue (), llvmTrueBlock, llvmFalseBlock);

    return statement_emit_result (result, nullptr);
}
