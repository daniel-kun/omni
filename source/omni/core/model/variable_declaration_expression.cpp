#include <omni/core/model/variable_declaration_expression.hpp>
#include <omni/core/model/type.hpp>
#include <omni/core/model/expression.hpp>
#include <omni/core/model/variable_assignment_expression.hpp>

#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/NoFolder.h>

omni::core::model::variable_declaration_expression::variable_declaration_expression () :
    pure_expression (),
    _type (),
    _llvmPointerValue (nullptr)
{
}

/**
@param variableType The type of the variable.
**/
omni::core::model::variable_declaration_expression::variable_declaration_expression (std::shared_ptr <omni::core::model::type> type) :
    pure_expression (),
    _type (type),
    _llvmPointerValue (nullptr)
{
}

/**
**/
omni::core::model::variable_declaration_expression::variable_declaration_expression (std::shared_ptr <omni::core::model::expression> initializer) :
    pure_expression (),
    _type (),
    _llvmPointerValue (nullptr)
{
    setInitializationExpression (initializer);
}

omni::core::domain omni::core::model::variable_declaration_expression::getDomain () const
{
    return domain::variable_declaration_expression;
}

/**
Returns the type of this variable_declaration_expression.
**/
std::shared_ptr <omni::core::model::type> omni::core::model::variable_declaration_expression::getType () const
{
    return _type;
}

/**
Changes the type of this variable to `type' and sets the initializer to nullptr.
**/
void omni::core::model::variable_declaration_expression::setType (std::shared_ptr <omni::core::model::type> type)
{
    _type = type;
    removeComponent (domain::expression, "initializer");
}

/**
Returns the expression that this variable will be initialized with. Can be nullptr.
**/
std::shared_ptr <omni::core::model::expression> omni::core::model::variable_declaration_expression::getInitializationExpression () const
{
    return getComponentAs <expression> (domain::expression, "initializer");
}

/**
Sets the initialization-expression of this varibale to `initializer' and changes this variable's type to the type of the expression.
**/
void omni::core::model::variable_declaration_expression::setInitializationExpression (std::shared_ptr <omni::core::model::expression> initializer)
{
    setComponent (domain::expression, "initializer", initializer);
    _type = initializer->getType ();
}

/**
Internal
**/
llvm::Value * omni::core::model::variable_declaration_expression::llvmPointerValue ()
{
    return _llvmPointerValue;
}

omni::core::statement_emit_result omni::core::model::variable_declaration_expression::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    llvm::IRBuilder <true, llvm::NoFolder> builder (llvmBasicBlock);
    _llvmPointerValue = builder.CreateAlloca (_type->llvmType ());
    std::shared_ptr <expression> initializationExpression = getInitializationExpression ();
    if (initializationExpression != nullptr) {
        return variable_assignment_expression::llvmEmitImpl (llvmBasicBlock, * this, * initializationExpression);
    } else {
        return statement_emit_result (llvmBasicBlock, builder.CreateLoad (_llvmPointerValue));
    }
}
 
