#include <omni/take2/expression_statement.hpp>
#include <omni/take2/expression.hpp>

omni::take2::expression_statement::expression_statement (std::shared_ptr <expression> expression) :
    _expression (expression)
{
}

void omni::take2::expression_statement::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    _expression->llvmValue (llvmBasicBlock);
}
