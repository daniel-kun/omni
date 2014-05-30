#include <omni/core/model/return_statement.hpp>
#include <omni/core/model/expression.hpp>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/NoFolder.h>

omni::core::model::return_statement::return_statement () :
    statement ()
{
}

omni::core::model::return_statement::return_statement (std::shared_ptr <expression> expression) :
    statement ()
{
    setExpression (expression);
}

std::shared_ptr <omni::core::model::expression> omni::core::model::return_statement::getExpression ()
{
    return getComponentAs <expression> (domain::expression, "expression");
}

const std::shared_ptr <omni::core::model::expression> omni::core::model::return_statement::getExpression () const
{
    return getComponentAs <expression> (domain::expression, "expression");
}

void omni::core::model::return_statement::setExpression (std::shared_ptr <omni::core::model::expression> expression)
{
    return setComponent (domain::expression, "expression", expression);
}

omni::core::statement_emit_result omni::core::model::return_statement::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    llvm::IRBuilder <true, llvm::NoFolder> builder (llvmBasicBlock);
    std::shared_ptr <expression> expression = getExpression ();
    if (expression.get () == nullptr) {
        builder.CreateRetVoid ();
    } else {
        builder.CreateRet (expression->llvmEmit (llvmBasicBlock).getValue ());
    }
    return statement_emit_result (llvmBasicBlock, nullptr);
}
