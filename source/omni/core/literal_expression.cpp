#include <omni/core/literal_expression.hpp>
#include <omni/core/literal.hpp>

omni::core::literal_expression::literal_expression(std::shared_ptr <literal> literal) :
    _literal (literal)
{
}

std::shared_ptr <omni::core::type> omni::core::literal_expression::getType () const
{
    return _literal->getType ();
}

omni::core::statement_emit_result omni::core::literal_expression::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    return statement_emit_result (llvmBasicBlock, _literal->llvmValue ());
}
