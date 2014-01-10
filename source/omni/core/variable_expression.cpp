#include <omni/core/variable_expression.hpp>
#include <omni/core/variable_declaration_statement.hpp>
#include <omni/core/use_before_declaration_error.hpp>
#include <omni/core/type.hpp>
#include <omni/core/domain.hpp>

#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/NoFolder.h>

/**
Initializes this expression to return variable's at the time this expression is executed.
**/
omni::core::variable_expression::variable_expression (std::shared_ptr <omni::core::variable_declaration_statement> variable) :
    _variable (variable)
{
}

std::shared_ptr <omni::core::type> omni::core::variable_expression::getType () const
{
    return _variable->getVariableType ();
}

/**
Returns the variable which value this expression returns.
**/
const std::shared_ptr <omni::core::variable_declaration_statement> omni::core::variable_expression::getVariable () const
{
    return _variable;
}

omni::core::statement_emit_result omni::core::variable_expression::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    llvm::Value * pointerValue = _variable->llvmPointerValue ();
    if (pointerValue == nullptr) {
        throw use_before_declaration_error (omni::core::domain::variable, _variable->getName ());
    }
    llvm::IRBuilder <true, llvm::NoFolder> builder (llvmBasicBlock);
    return statement_emit_result (llvmBasicBlock, builder.CreateLoad (pointerValue));
}
