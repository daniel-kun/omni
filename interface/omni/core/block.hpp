#ifndef OMNI_CORE_BLOCK_HPP
#define OMNI_CORE_BLOCK_HPP

#include <omni/core/core.hpp>
#include <omni/core/context_part.hpp>

#include <vector>
#include <memory>

namespace omni {
namespace core {
    class statement;

    /**
    A block is a list of statements that is executed in a specific context. Examples are function bodies and bodies of an 'if', 'else', 'while' or 'for'-statement.
    **/
    class OMNI_CORE_API block : public context_part {
    public:
        const std::vector <std::shared_ptr <statement> > getStatements () const;

        std::shared_ptr <statement> prependStatement (std::shared_ptr <statement> statement); // TODO
        std::shared_ptr <statement> appendStatement (std::shared_ptr <statement> statement);
        std::shared_ptr <statement> insertStatementAfter (std::vector <std::shared_ptr <statement>>::iterator position); // TODO
        std::shared_ptr <statement> insertStatementBefore (std::vector <std::shared_ptr <statement>>::iterator position); // TODO
        std::shared_ptr <statement> removeStatement (std::vector <std::shared_ptr <statement>>::iterator position); // TODO

    private:
        std::vector <std::shared_ptr <statement>> _statements;
    };
    
} // namespace core
} // namespace omni

#endif // include guard
