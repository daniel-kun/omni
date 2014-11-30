#ifndef OMNI_CORE_IF_STATEMENT_HPP
#define OMNI_CORE_IF_STATEMENT_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/statement.hpp>

#include <memory>

namespace omni {
namespace core {
namespace model {
    class block;
    class expression;

    /**
    An if_statement executes either the trueBlock or the elseBlock depending on a condition.
    The conditon and the trueBlock are necessary, the elseBlock is optional.
    **/
    class OMNI_CORE_API if_statement : public statement {
    public:
        if_statement (std::shared_ptr <expression> condition, std::shared_ptr <block> trueBlock, std::shared_ptr <block> elseBlock);

        static meta_info & getStaticMetaInfo ();

        meta_info & getMetaInfo () const override;

        domain getDomain () const override;

        void setCondition (std::shared_ptr <expression> condition);
        std::shared_ptr <expression> getCondition ();
        const std::shared_ptr <expression> getCondition () const;

        void setTrueBlock (std::shared_ptr <block> trueBlock);
        std::shared_ptr <block> getTrueBlock ();
        const std::shared_ptr <block> getTrueBlock () const;

        void setElseBlock (std::shared_ptr <block> elseBlock);
        std::shared_ptr <block> getElseBlock ();
        const std::shared_ptr <block> getElseBlock () const;

        statement_emit_result llvmEmit (llvm::BasicBlock * llvmBasicBlock) override;
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
