#include <omni/core/statement_emit_result.hpp>

/**
Initializes this result with the given continueBlock and the given value
@param continueBlock The block that should be used to emit following statements. Some statements branch a new block and use the continueBlock
to return this new block to the llvm emitting code. If the statement does not branch, continueBlock should be set to the same as the llvmBasicBlock
provided to omni::core::statement::llvmEmit. @see getContinueBlock().
@param value nullptr for statements that are not expressions. Expressions return their result value with this field. @see getValue() @see hasValue().
**/
omni::core::statement_emit_result::statement_emit_result (llvm::BasicBlock * continueBlock, llvm::Value * value) :
    _continueBlock (continueBlock),
    _value (value)
{
}

/**
Returns the block that should be used for further emitting code after this statement has been emitted. This is used for branching statements.
**/
llvm::BasicBlock * omni::core::statement_emit_result::getContinueBlock () const
{
    return _continueBlock;
}

/**
If the statement is an expression, getValue returns the expression's value. Is always nullptr for all statements that are not expressions.
**/
llvm::Value * omni::core::statement_emit_result::getValue () const
{
    return _value;
}

/**
Returns true, when this statement has a value (i.e. is an expression).
**/
bool omni::core::statement_emit_result::hasValue () const
{
    return _value != nullptr;
}
