#include <omni/take2/literal_expression.hpp>
#include <omni/take2/literal.hpp>

omni::take2::literal_expression::literal_expression(std::shared_ptr <literal> literal) :
    _literal (literal)
{
}

llvm::Value * omni::take2::literal_expression::llvmValue (llvm::BasicBlock * llvmBasicBlock)
{
    return _literal->llvmValue ();
}
