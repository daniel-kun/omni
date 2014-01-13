#include <omni/core/block.hpp>
#include <omni/core/statement.hpp>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/BasicBlock.h>

/**
@return Returns the list of statements that this block contains.
**/
const std::vector <std::shared_ptr <omni::core::statement> > omni::core::block::getStatements () const
{
    return _statements;
}

/**
Returns an iterator to the given statement that exists in the list of statements that this lock contains.
Can return getStatements ().end () if the statement is not listed in this block.
**/
omni::core::block::statement_list::iterator omni::core::block::findStatement (std::shared_ptr <statement> statement)
{
    return std::find (_statements.begin (), _statements.end (), statement);
}

/**
Appends the given statement to the list of statements that this block contains.
@return Returns the statement that has been added.
**/
std::shared_ptr <omni::core::statement> omni::core::block::appendStatement (std::shared_ptr <omni::core::statement> statement)
{
    _statements.push_back (statement);
    return statement;
}

/**
Inserts the given statement at the beginning of the list of statements that this block contains.
@return Returns the statement that has been added.
**/
std::shared_ptr <omni::core::statement> omni::core::block::prependStatement (std::shared_ptr <omni::core::statement> statement)
{
    _statements.insert (_statements.begin (), statement);
    return statement;
}

/**
Inserts the given statement after the provided position in the list of statements that this block contains.
Use the vector returned by findStatement to determine the position.
@return Returns the statement that has been added.
**/
std::shared_ptr <omni::core::statement> omni::core::block::insertStatementAfter (statement_list::iterator position, std::shared_ptr <statement> statement)
{
    _statements.insert (++position, statement);
    return statement;
}

/**
Inserts the given statement before the provided position in the list of statements that this block contains.
Use the vector returned by findStatement to determine the position.
@return Returns the statement that has been added.
**/
std::shared_ptr <omni::core::statement> omni::core::block::insertStatementBefore (statement_list::iterator position, std::shared_ptr <statement> statement)
{
    _statements.insert (position, statement);
    return statement;
}

/**
Removes the statement at the given position from the list of statements that this block contains.
@return Returns the statement that has been removed.
**/
std::shared_ptr <omni::core::statement> omni::core::block::removeStatement (statement_list::iterator position)
{
    std::shared_ptr <statement> result = * position;
    _statements.erase (position);
    return result;
}

/**
Removes the given statement from the list of statements that this block contains.
@return Returns the statement that has been removed.
**/
std::shared_ptr <omni::core::statement> omni::core::block::removeStatement (std::shared_ptr <statement> statement)
{
    statement_list::iterator i = std::find (_statements.begin (), _statements.end (), statement);
    _statements.erase (i);
    return statement;
}

/**
@internal
**/
llvm::BasicBlock * omni::core::block::llvmEmitIntoExistingBlock (llvm::BasicBlock * llvmBasicBlock)
{
    llvm::BasicBlock * block = llvmBasicBlock;
    for (auto i : getStatements ()) {
        block = i->llvmEmit (block).getContinueBlock ();
    }
    return block;
}

/**
@internal
**/
omni::core::statement_emit_result omni::core::block::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    auto result = llvm::BasicBlock::Create (llvmBasicBlock->getContext (), "", llvmBasicBlock->getParent ());
    for (auto i : getStatements ()) {
        result = i->llvmEmit (result).getContinueBlock ();
    }
    return statement_emit_result (result, nullptr);
}
