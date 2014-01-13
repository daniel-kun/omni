#include <omni/core/model/variable_expression.hpp>
#include <omni/core/model/variable_declaration_expression.hpp>
#include <omni/core/model/use_before_declaration_error.hpp>
#include <omni/core/model/type.hpp>
#include <omni/core/domain.hpp>

#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/NoFolder.h>

/**
Initializes this expression to return variable's at the time this expression is executed.
**/
omni::core::model::variable_expression::variable_expression (std::shared_ptr <variable_declaration_expression> variable) :
    _variable (variable)
{
}

std::shared_ptr <omni::core::model::type> omni::core::model::variable_expression::getType () const
{
    return _variable->getType ();
}

/**
Returns the variable which value this expression returns.
**/
const std::shared_ptr <omni::core::model::variable_declaration_expression> omni::core::model::variable_expression::getVariable () const
{
    return _variable;
}

omni::core::statement_emit_result omni::core::model::variable_expression::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    llvm::Value * pointerValue = _variable->llvmPointerValue ();
    if (pointerValue == nullptr) {
        throw use_before_declaration_error (omni::core::domain::variable, _variable->getName ());
    }
    llvm::IRBuilder <true, llvm::NoFolder> builder (llvmBasicBlock);
    return statement_emit_result (llvmBasicBlock, builder.CreateLoad (pointerValue));
}
