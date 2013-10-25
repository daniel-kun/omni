#ifndef OMNI_TAKE2_BLOCK_HPP
#define OMNI_TAKE2_BLOCK_HPP

#include <omni/take2/take2.hpp>
#include <omni/take2/context_part.hpp>
#include <vector>
#include <memory>

namespace omni {
namespace take2 {
    class statement;

	class OMNI_TAKE2_API block : public context_part {
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
	
} // namespace take2
} // namespace omni

#endif // include guard
