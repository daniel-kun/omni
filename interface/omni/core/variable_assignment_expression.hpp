#ifndef OMNI_CORE_VARIABLE_ASSIGNMENT_EXPRESSION_HPP
#define OMNI_CORE_VARIABLE_ASSIGNMENT_EXPRESSION_HPP

#include <omni/core/core.hpp>
#include <omni/core/modifying_expression.hpp>

#include <memory>

namespace omni {
namespace core {
namespace model {
    class variable_declaration_expression;

    /**
    A variable_assignment_expression changes the value of a variable to the return value of any expression.
    This variable_assignment_expression needs to be either used by another expression or statement to be executed.
    It can be put into a block if the assignment of the variable should be the only affect.
    Otherwise, it can be used as a parameter to a function call, as a left or right hand side operand of a binary_operator_expression, etc.
    **/
    class OMNI_CORE_API variable_assignment_expression : public modifying_expression {
    public:
        variable_assignment_expression (std::shared_ptr <variable_declaration_expression> variable, std::shared_ptr <expression> value);

        std::shared_ptr <variable_declaration_expression> getVariable () const;
        std::shared_ptr <expression> getValue () const;

        std::shared_ptr <type> getType () const override;

        statement_emit_result llvmEmit (llvm::BasicBlock * llvmBasicBlock) override;
        static statement_emit_result llvmEmitImpl (llvm::BasicBlock * llvmBasicBlock, variable_declaration_expression & variable, expression & value);
    private:
        std::shared_ptr <variable_declaration_expression> _variable;
        std::shared_ptr <expression> _value;
        llvm::Value * _llvmValue;
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
