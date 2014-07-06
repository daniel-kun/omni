#include <omni/core/model/variable_assignment_expression.hpp>
#include <omni/core/model/variable_declaration_expression.hpp>
#include <omni/core/model/type_mismatch_error.hpp>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/NoFolder.h>

/**
Initializes this variabe_assignment_expresion to assign `value' to `variable'.
variable and value need to be of exactly the same type.
**/
omni::core::model::variable_assignment_expression::variable_assignment_expression (std::shared_ptr <variable_declaration_expression> variable, std::shared_ptr <expression> value) :
    modifying_expression (),
    _variable (variable),
    _llvmValue (nullptr)
{
    setValue (value);
    if (_variable->getType () != value->getType ()) {
        throw type_mismatch_error (* _variable->getType (), * value->getType ());
    }
}

omni::core::domain omni::core::model::variable_assignment_expression::getDomain () const
{
    return domain::variable_assignment_expression;
}

void omni::core::model::variable_assignment_expression::setVariable (std::shared_ptr <omni::core::model::variable_declaration_expression> variable)
{
    _variable = variable;
}


/**
Returns the variable that is being assigned to by this expression.
**/
std::shared_ptr <omni::core::model::variable_declaration_expression> omni::core::model::variable_assignment_expression::getVariable () const
{
    return _variable;
}

void omni::core::model::variable_assignment_expression::setValue (std::shared_ptr <omni::core::model::expression> value)
{
    setComponent (domain::expression, "value", value);
}


/**
Returns the value that is being assigned to a variable by this expression.
**/
std::shared_ptr <omni::core::model::expression> omni::core::model::variable_assignment_expression::getValue () const
{
    return getComponentAs <expression> (domain::expression, "value");
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
    return variable_assignment_expression::llvmEmitImpl (llvmBasicBlock, * _variable, * getValue ());
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
