#include <omni/core/model/literal_expression.hpp>
#include <omni/core/model/literal.hpp>

omni::core::model::literal_expression::literal_expression (omni::core::model::scope & parent) :
    pure_expression (parent),
    _literal ()
{
}

std::shared_ptr <omni::core::model::literal> omni::core::model::literal_expression::getLiteral ()
{
    return _literal;
}

const std::shared_ptr <omni::core::model::literal> omni::core::model::literal_expression::getLiteral () const
{
    return _literal;
}

void omni::core::model::literal_expression::setLiteral (std::shared_ptr <omni::core::model::literal> literal)
{
    _literal = literal;
}

std::shared_ptr <omni::core::model::type> omni::core::model::literal_expression::getType () const
{
    return _literal->getType ();
}

omni::core::statement_emit_result omni::core::model::literal_expression::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    return statement_emit_result (llvmBasicBlock, _literal->llvmValue ());
}
