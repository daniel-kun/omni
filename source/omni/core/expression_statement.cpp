#include <omni/core/expression_statement.hpp>
#include <omni/core/expression.hpp>

omni::core::expression_statement::expression_statement (std::shared_ptr <expression> expression) :
    _expression (expression)
{
}

llvm::BasicBlock * omni::core::expression_statement::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    _expression->llvmValue (llvmBasicBlock);
    return llvmBasicBlock;
}
