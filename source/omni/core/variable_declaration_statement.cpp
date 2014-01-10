#include <omni/core/variable_declaration_statement.hpp>
#include <omni/core/type.hpp>
#include <omni/core/expression.hpp>
#include <omni/core/variable_assignment_expression.hpp>

#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/Support/NoFolder.h>

/**
Initializes this variable_declaration_statement with the type variableType. The variable will be initialized with the default value of that type.
@param variableType The type of the variable.
**/
omni::core::variable_declaration_statement::variable_declaration_statement (std::shared_ptr <omni::core::type> variableType) :
    _variableType (variableType),
    _initializationExpression (),
    _llvmPointerValue (nullptr)
{
}

/**
Initializes this variable_declaration_statement with the type of initializationExpression. The variable will be initialized with the result of initializationExpression.
@param initializationExpression The expression that this variable's type will be deduced from and with which result this variable will be initialized with.
May not be nullptr. Use the ctor that takes a omni::core::type when you want to create a variable_declaration_statement that is initialized with the default value of the corresponding type.
**/
omni::core::variable_declaration_statement::variable_declaration_statement (std::shared_ptr <omni::core::expression> initializationExpression) :
    _variableType (initializationExpression->getType ()),
    _initializationExpression (initializationExpression),
    _llvmPointerValue (nullptr)
{
}

/**
Returns the type of this variable_declaration_statement.
**/
std::shared_ptr <omni::core::type> omni::core::variable_declaration_statement::getVariableType () const
{
    return _variableType;
}

/**
Returns the expression that this variable will be initialized with. Can be nullptr.
**/
std::shared_ptr <omni::core::expression> omni::core::variable_declaration_statement::getInitializationExpression () const
{
    return _initializationExpression;
}

/**
Internal
**/
llvm::Value * omni::core::variable_declaration_statement::llvmPointerValue ()
{
    return _llvmPointerValue;
}

omni::core::statement_emit_result omni::core::variable_declaration_statement::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    llvm::IRBuilder <true, llvm::NoFolder> builder (llvmBasicBlock);
    _llvmPointerValue = builder.CreateAlloca (_variableType->llvmType ());
    if (_initializationExpression != nullptr) {
        variable_assignment_expression::llvmEmitImpl (llvmBasicBlock, * this, * _initializationExpression);
    }
    return statement_emit_result (llvmBasicBlock, nullptr);
}
