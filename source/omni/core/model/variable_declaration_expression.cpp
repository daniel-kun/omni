#include <omni/core/model/variable_declaration_expression.hpp>
#include <omni/core/model/type.hpp>
#include <omni/core/model/expression.hpp>
#include <omni/core/model/variable_assignment_expression.hpp>

#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/Support/NoFolder.h>

/**
Initializes this variable_declaration_expression with the type variableType. The variable will be initialized with the default value of that type.
@param variableType The type of the variable.
**/
omni::core::model::variable_declaration_expression::variable_declaration_expression (std::shared_ptr <type> variableType) :
    _type (variableType),
    _initializationExpression (),
    _llvmPointerValue (nullptr)
{
}

/**
Initializes this variable_declaration_expression with the type of initializationExpression. The variable will be initialized with the result of initializationExpression.
@param initializationExpression The expression that this variable's type will be deduced from and with which result this variable will be initialized with.
May not be nullptr. Use the ctor that takes a omni::core::model::type when you want to create a variable_declaration_expression that is initialized with the default value of the corresponding type.
**/
omni::core::model::variable_declaration_expression::variable_declaration_expression (std::shared_ptr <expression> initializationExpression) :
    _type (initializationExpression->getType ()),
    _initializationExpression (initializationExpression),
    _llvmPointerValue (nullptr)
{
}

/**
Returns the type of this variable_declaration_expression.
**/
std::shared_ptr <omni::core::model::type> omni::core::model::variable_declaration_expression::getType () const
{
    return _type;
}

/**
Returns the expression that this variable will be initialized with. Can be nullptr.
**/
std::shared_ptr <omni::core::model::expression> omni::core::model::variable_declaration_expression::getInitializationExpression () const
{
    return _initializationExpression;
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
    if (_initializationExpression != nullptr) {
        return variable_assignment_expression::llvmEmitImpl (llvmBasicBlock, * this, * _initializationExpression);
    } else {
        return statement_emit_result (llvmBasicBlock, builder.CreateLoad (_llvmPointerValue));
    }
}
