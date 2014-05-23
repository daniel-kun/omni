#include <omni/core/model/variable_assignment_expression.hpp>
#include <omni/core/model/variable_declaration_expression.hpp>
#include <omni/core/model/type_mismatch_error.hpp>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/NoFolder.h>

/**
Initializes this variabe_assignment_expresion to assign `value' to `variable'.
variable and value need to be of exactly the same type.
**/
omni::core::model::variable_assignment_expression::variable_assignment_expression (std::shared_ptr <variable_declaration_expression> variable, std::shared_ptr <expression> value) :
    _variable (variable),
    _value (value),
    _llvmValue (nullptr)
{
    if (_variable->getType () != _value->getType ()) {
        throw type_mismatch_error (* _variable->getType (), * _value->getType ());
    }
}

/**
Returns the variable that is being assigned to by this expression.
**/
std::shared_ptr <omni::core::model::variable_declaration_expression> omni::core::model::variable_assignment_expression::getVariable () const
{
    return _variable;
}

/**
Returns the value that is being assigned to a variable by this expression.
**/
std::shared_ptr <omni::core::model::expression> omni::core::model::variable_assignment_expression::getValue () const
{
    return _value;
}

std::shared_ptr <omni::core::model::type> omni::core::model::variable_assignment_expression::getType () const
{
    return _variable->getType ();
}

/**
Internal
**/
omni::core::statement_emit_result omni::core::model::variable_assignment_expression::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    return variable_assignment_expression::llvmEmitImpl (llvmBasicBlock, * _variable, * _value);
}

/**
Internal
**/
omni::core::statement_emit_result omni::core::model::variable_assignment_expression::llvmEmitImpl (llvm::BasicBlock * llvmBasicBlock, variable_declaration_expression & variable, expression & value)
{
    llvm::IRBuilder <true, llvm::NoFolder> builder (llvmBasicBlock);
    statement_emit_result result = value.llvmEmit (llvmBasicBlock);
    builder.CreateStore (result.getValue (), variable.llvmPointerValue ());
    return result;
}
