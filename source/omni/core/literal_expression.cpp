#include <omni/core/literal_expression.hpp>
#include <omni/core/literal.hpp>

omni::core::literal_expression::literal_expression(std::shared_ptr <literal> literal) :
    _literal (literal)
{
}

llvm::Value * omni::core::literal_expression::llvmValue (llvm::BasicBlock * llvmBasicBlock)
{
    return _literal->llvmValue ();
}
