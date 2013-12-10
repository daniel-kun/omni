#include <omni/core/block.hpp>

const std::vector <std::shared_ptr <omni::core::statement> > omni::core::block::getStatements () const
{
    return _statements;
}

std::shared_ptr <omni::core::statement> omni::core::block::appendStatement (std::shared_ptr <omni::core::statement> statement)
{
    _statements.push_back (statement);
    return statement;
}
