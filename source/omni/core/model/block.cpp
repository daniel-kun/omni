#include <omni/core/model/block.hpp>
#include <omni/core/model/statement.hpp>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/BasicBlock.h>

#include <boost/lexical_cast.hpp>

// See meta_info.cpp for initialization.
namespace omniMetaImpl {
extern omni::core::model::meta_info blockMetaInfo;
}

omni::core::model::block::block () :
    statement (),
    _statementCount (0u)
{
}

omni::core::model::meta_info & omni::core::model::block::getStaticMetaInfo ()
{
    return omniMetaImpl::blockMetaInfo;
}

omni::core::model::meta_info & omni::core::model::block::getMetaInfo () const
{
    return getStaticMetaInfo ();
}

omni::core::domain omni::core::model::block::getDomain () const
{
    return domain::block;
}

/**
@return Returns the list of statements that this block contains.
**/
const std::vector <std::shared_ptr <omni::core::model::statement> > omni::core::model::block::getStatements () const
{
    return _statements;
}

/**
Returns an iterator to the given statement that exists in the list of statements that this lock contains.
Can return getStatements ().end () if the statement is not listed in this block.
**/
omni::core::model::block::statement_list::iterator omni::core::model::block::findStatement (std::shared_ptr <statement> statement)
{
    return std::find (_statements.begin (), _statements.end (), statement);
}

/**
Returns the end of the statement_list. Can be used to check, whether findStatement retuned a valid result.
**/
omni::core::model::block::statement_list::iterator omni::core::model::block::statementsEnd ()
{
    return _statements.end ();
}

/**
Appends the given statement to the list of statements that this block contains.
@return Returns the statement that has been added.
**/
std::shared_ptr <omni::core::model::statement> omni::core::model::block::appendStatement (std::shared_ptr <statement> statement)
{
    _statements.push_back (statement);
    setComponent (domain::statement, "statement" + boost::lexical_cast <std::string> (++_statementCount), statement);
    return statement;
}

/**
Inserts the given statement at the beginning of the list of statements that this block contains.
@return Returns the statement that has been added.
**/
std::shared_ptr <omni::core::model::statement> omni::core::model::block::prependStatement (std::shared_ptr <statement> statement)
{
    _statements.insert (_statements.begin (), statement);
    setComponent (domain::statement, "statement" + boost::lexical_cast <std::string> (++_statementCount), statement);
    return statement;
}

/**
Inserts the given statement after the provided position in the list of statements that this block contains.
Use the vector returned by findStatement to determine the position.
@return Returns the statement that has been added.
**/
std::shared_ptr <omni::core::model::statement> omni::core::model::block::insertStatementAfter (statement_list::iterator position, std::shared_ptr <statement> statement)
{
    _statements.insert (++position, statement);
    setComponent (domain::statement, "statement" + boost::lexical_cast <std::string> (++_statementCount), statement);
    return statement;
}

/**
Inserts the given statement before the provided position in the list of statements that this block contains.
Use the vector returned by findStatement to determine the position.
@return Returns the statement that has been added.
**/
std::shared_ptr <omni::core::model::statement> omni::core::model::block::insertStatementBefore (statement_list::iterator position, std::shared_ptr <statement> statement)
{
    _statements.insert (position, statement);
    setComponent (domain::statement, "statement" + boost::lexical_cast <std::string> (++_statementCount), statement);
    return statement;
}

/**
Removes the statement at the given position from the list of statements that this block contains.
@return Returns the statement that has been removed.
**/
std::shared_ptr <omni::core::model::statement> omni::core::model::block::removeStatement (statement_list::iterator position)
{
    std::shared_ptr <statement> result = * position;
    _statements.erase (position);
    for (auto i : getComponentsStartingWithAs <statement> (domain::statement, "statement")) {
        if (i.second == result) {
            removeComponent (domain::statement, i.first);
            break;
        }
    }
    return result;
}

/**
Removes the given statement from the list of statements that this block contains.
@return Returns the statement that has been removed.
**/
std::shared_ptr <omni::core::model::statement> omni::core::model::block::removeStatement (std::shared_ptr <statement> statement)
{
    statement_list::iterator i = std::find (_statements.begin (), _statements.end (), statement);
    return removeStatement (i);
}

/**
@internal
**/
llvm::BasicBlock * omni::core::model::block::llvmEmitIntoExistingBlock (llvm::BasicBlock * llvmBasicBlock)
{
    llvm::BasicBlock * block = llvmBasicBlock;
    for (auto i : _statements) {
        block = i->llvmEmit (block).getContinueBlock ();
    }
    return block;
}

/**
@internal
**/
omni::core::statement_emit_result omni::core::model::block::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    auto result = llvm::BasicBlock::Create (llvmBasicBlock->getContext (), "", llvmBasicBlock->getParent ());
    for (auto i : _statements) {
        result = i->llvmEmit (result).getContinueBlock ();
    }
    return statement_emit_result (result, nullptr);
}
