#include <omni/core/model/do_while_statement.hpp>
#include <omni/core/model/block.hpp>
#include <omni/core/model/expression.hpp>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/NoFolder.h>

// See meta_info.cpp for initialization.
namespace omniMetaImpl {
extern omni::core::model::meta_info do_while_statementMetaInfo;
}

omni::core::model::do_while_statement::do_while_statement () :
    while_statement ()
{
}

omni::core::model::do_while_statement::do_while_statement (std::shared_ptr <omni::core::model::expression> condition, std::shared_ptr <omni::core::model::block> body) :
    while_statement (condition, body)
{
}

omni::core::model::meta_info & omni::core::model::do_while_statement::getStaticMetaInfo ()
{
    return omniMetaImpl::do_while_statementMetaInfo;
}

omni::core::model::meta_info & omni::core::model::do_while_statement::getMetaInfo () const
{
    return getStaticMetaInfo ();
}

omni::core::domain omni::core::model::do_while_statement::getDomain () const
{
    return domain::do_while_statement;
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
