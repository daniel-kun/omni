#ifndef OMNI_CORE_WHILE_STATEMENT_HPP
#define OMNI_CORE_WHILE_STATEMENT_HPP

#include <omni/core/core.hpp>
#include <omni/core/statement.hpp>

#include <memory>

namespace omni {
namespace core {
    class block;
    class expression;

    /**
    An while_statement executes the body as long as condition is true.
    **/
    class OMNI_CORE_API while_statement : public statement {
    public:
        while_statement (std::shared_ptr <expression> condition, std::shared_ptr <block> body);

        std::shared_ptr <expression> getCondition ();
        const std::shared_ptr <expression> getCondition () const;

        std::shared_ptr <block> getBody ();
        const std::shared_ptr <block> getBody () const;

        llvm::BasicBlock * llvmEmit (llvm::BasicBlock * llvmBasicBlock) override;

    private:
        std::shared_ptr <expression> _condition;
        std::shared_ptr <block> _body;
    };
    
} // namespace core
} // namespace omni

#endif // include guard
