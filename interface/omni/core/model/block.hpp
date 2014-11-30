#ifndef OMNI_CORE_BLOCK_HPP
#define OMNI_CORE_BLOCK_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/statement.hpp>

#include <vector>
#include <memory>

namespace llvm {
    class LLVMContext;
    class BasicBlock;
    class Function;
}

namespace omni {
namespace core {
namespace model {
    class statement;

    /**
    A block is a list of statements that is executed in a specific context. Examples are function bodies and bodies of an 'if', 'else', 'while' or 'for'-statement.
    **/
    class OMNI_CORE_API block : public statement {
    public:
        typedef std::vector <std::shared_ptr <statement>> statement_list;

        block ();

        static meta_info & getStaticMetaInfo ();

        meta_info & getMetaInfo () const override;

        domain getDomain () const override;

        const statement_list getStatements () const;
        statement_list::iterator findStatement (std::shared_ptr <statement> statement);
        statement_list::iterator statementsEnd ();

        std::shared_ptr <statement> prependStatement (std::shared_ptr <statement> statement);
        std::shared_ptr <statement> appendStatement (std::shared_ptr <statement> statement);
        std::shared_ptr <statement> insertStatementAfter (statement_list::iterator position, std::shared_ptr <statement> statement);
        std::shared_ptr <statement> insertStatementBefore (statement_list::iterator position, std::shared_ptr <statement> statement);
        std::shared_ptr <statement> removeStatement (statement_list::iterator position);
        std::shared_ptr <statement> removeStatement (std::shared_ptr <statement> statement);

        llvm::BasicBlock * llvmEmitIntoExistingBlock (llvm::BasicBlock * llvmBasicBlock);
        statement_emit_result llvmEmit (llvm::BasicBlock * llvmBasicBlock) override;
    private:
        std::size_t _statementCount;
        statement_list _statements;
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
