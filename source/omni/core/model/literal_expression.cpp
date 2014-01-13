#include <omni/core/model/literal_expression.hpp>
#include <omni/core/model/literal.hpp>

omni::core::model::literal_expression::literal_expression(std::shared_ptr <literal> literal) :
    _literal (literal)
{
}

std::shared_ptr <omni::core::model::type> omni::core::model::literal_expression::getType () const
{
    return _literal->getType ();
}

omni::core::statement_emit_result omni::core::model::literal_expression::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    return statement_emit_result (llvmBasicBlock, _literal->llvmValue ());
}
