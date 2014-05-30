#ifndef OMNI_CORE_DO_WHILE_STATEMENT_HPP
#define OMNI_CORE_DO_WHILE_STATEMENT_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/while_statement.hpp>

#include <memory>

namespace omni {
namespace core {
namespace model {
    class block;
    class expression;

    /**
    An do_while_statement executes the body in a loop and exits the loop when the condition is false.
    **/
    class OMNI_CORE_API do_while_statement : public while_statement {
    public:
        do_while_statement ();
        do_while_statement (std::shared_ptr <expression> condition, std::shared_ptr <block> body);

        statement_emit_result llvmEmit (llvm::BasicBlock * llvmBasicBlock) override;

    private:
    };
    
} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
