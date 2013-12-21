#ifndef OMNI_CORE_IF_STATEMENT_HPP
#define OMNI_CORE_IF_STATEMENT_HPP

#include <omni/core/core.hpp>
#include <omni/core/statement.hpp>

#include <memory>

namespace omni {
namespace core {
    class block;
    class expression;

    /**
    An if_statement executes either the trueBlock or the elseBlock depending on a condition.
    The conditon and the trueBlock are necessary, the elseBlock is optional.
    **/
    class OMNI_CORE_API if_statement : public statement {
    public:
        if_statement (std::shared_ptr <expression> condition, std::shared_ptr <block> trueBlock, std::shared_ptr <block> elseBlock);

        std::shared_ptr <expression> getCondition ();
        const std::shared_ptr <expression> getCondition () const;

        std::shared_ptr <block> getTrueBlock ();
        const std::shared_ptr <block> getTrueBlock () const;

        std::shared_ptr <block> getElseBlock ();
        const std::shared_ptr <block> getElseBlock () const;

        llvm::BasicBlock * llvmEmit (llvm::BasicBlock * llvmBasicBlock) override;

    private:
        std::shared_ptr <expression> _condition;
        std::shared_ptr <block> _trueBlock;
        std::shared_ptr <block> _elseBlock; // May be null
    };
    
} // namespace core
} // namespace omni

#endif // include guard
