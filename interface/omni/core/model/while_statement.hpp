#ifndef OMNI_CORE_WHILE_STATEMENT_HPP
#define OMNI_CORE_WHILE_STATEMENT_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/statement.hpp>

#include <memory>

namespace omni {
namespace core {
namespace model {
    class block;
    class expression;

    /**
    An while_statement executes the body as long as condition is true.
    **/
    class OMNI_CORE_API while_statement : public statement {
    public:
        while_statement ();
        while_statement (std::shared_ptr <expression> condition, std::shared_ptr <block> body);

        static meta_info & getStaticMetaInfo ();

        meta_info & getMetaInfo () const override;

        domain getDomain () const override;

        std::shared_ptr <expression> getCondition ();
        const std::shared_ptr <expression> getCondition () const;
        void setCondition (std::shared_ptr <expression> condition);

        std::shared_ptr <block> getBody ();
        const std::shared_ptr <block> getBody () const;
        void setBody (std::shared_ptr <block> body);

        statement_emit_result llvmEmit (llvm::BasicBlock * llvmBasicBlock) override;

    private:
        std::shared_ptr <expression> _condition;
        std::shared_ptr <block> _body;
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
