#include <omni/core/model/literal_expression.hpp>
#include <omni/core/model/literal.hpp>

omni::core::model::literal_expression::literal_expression () :
    pure_expression ()
{
}

omni::core::model::literal_expression::literal_expression (std::shared_ptr <omni::core::model::literal> literal) :
    pure_expression (),
    _literal (literal)
{
}

omni::core::domain omni::core::model::literal_expression::getDomain () const
{
    return domain::literal_expression;
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
    return getLiteral ()->getType ();
}

omni::core::statement_emit_result omni::core::model::literal_expression::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    return statement_emit_result (llvmBasicBlock, getLiteral ()->llvmValue ());
}
