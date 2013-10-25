#include <omni/take2/block.hpp>

const std::vector <std::shared_ptr <omni::take2::statement> > omni::take2::block::getStatements () const
{
    return _statements;
}

std::shared_ptr <omni::take2::statement> omni::take2::block::appendStatement (std::shared_ptr <omni::take2::statement> statement)
{
    _statements.push_back (statement);
    return statement;
}
