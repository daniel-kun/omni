#ifndef OMNI_CORE_LITERAL_EXPRESSION_HPP
#define OMNI_CORE_LITERAL_EXPRESSION_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/pure_expression.hpp>

#include <memory>

namespace omni {
namespace core {
namespace model {
    class literal;

    /**
    A literal expression is an expression that simply returns a value that was already defined at compile time.
    **/
    class OMNI_CORE_API literal_expression : public pure_expression {
    public:
        literal_expression ();
        literal_expression (std::shared_ptr <literal> literal);
        
        domain getDomain () const override;

        std::shared_ptr <literal> getLiteral ();
        const std::shared_ptr <literal> getLiteral () const;
        void setLiteral (std::shared_ptr <literal> literal);

        std::shared_ptr <type> getType () const override;

        statement_emit_result llvmEmit (llvm::BasicBlock * llvmBasicBlock) override;

    private:
        std::shared_ptr <literal> _literal;
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
