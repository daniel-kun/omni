#ifndef OMNI_CORE_VARIABLE_DECLARATION_EXPRESSION_HPP
#define OMNI_CORE_VARIABLE_DECLARATION_EXPRESSION_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/pure_expression.hpp>

namespace llvm {
    class Value;
}

namespace omni {
namespace core {
namespace model {
    class type;
    class expression;

    /**
    @class variable_declaration_expression variable_declaration_expression.hpp omni/core/model/variable_declaration_expression.hpp
    @brief A variable_declaration_expression is an expression that declares a variable and returns it's content.

    A variable declaration always contains a name. The properties of the variable are either defined by a specified type for the variable or by an initialization expression.
    
    If a type is specified, the variable is initialized with the type's default value - which means that the type needs to *have* a default value. This is guarantueed for all built-in types.
    Classes may not have a default constructor and hence do not have a default value.
    
    If an initialization expression is specified in a variable declaration, the variable's type is deduced from the expression's type and the value of the variable is initialized with the
    return value of the expression.

    As a variable declaration is an expression, it can be used wherever a value is needed. E.g. in the condition of an if-statement. The variable's scope is propagated across it's parent scope.
    This means if a variable is declared in a block, it is known across the block and all it's children. If it is declared in an if-statement's condition, it is known in all the children of the
    if-statement - this includes the true-block and the else-block.
    **/
    class OMNI_CORE_API variable_declaration_expression : public pure_expression {
    public:
        variable_declaration_expression ();
        variable_declaration_expression (std::shared_ptr <type> type);
        variable_declaration_expression (std::shared_ptr <expression> initializer);

        static meta_info & getStaticMetaInfo ();

        virtual meta_info & getMetaInfo () const;

        domain getDomain () const override;

        std::shared_ptr <type> getType () const override;
        void setType (std::shared_ptr <type> type);

        std::shared_ptr <expression> getInitializationExpression () const;
        void setInitializationExpression (std::shared_ptr <expression> initializer);

        llvm::Value * llvmPointerValue ();
        statement_emit_result llvmEmit (llvm::BasicBlock * llvmBasicBlock) override;

    private:
        std::shared_ptr <type> _type;
        llvm::Value * _llvmPointerValue; // internal
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
