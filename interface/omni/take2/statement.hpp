#ifndef OMNI_TAKE2_STATEMENT_HPP
#define OMNI_TAKE2_STATEMENT_HPP

#include <omni/take2/take2.hpp>
#include <omni/take2/context_part.hpp>

namespace llvm {
    class BasicBlock;
}

namespace omni {
namespace take2 {

	/**
	A statement can be anything that is being executed in a block. Statements do not have results. In contrast,
	expressions have results, that's why an expression can be a statement. In that case, the result is discarded.
	@see expression_statement.
	**/
	class OMNI_TAKE2_API statement : public context_part {
	public:
		virtual ~ statement ();
        virtual void llvmEmit (llvm::BasicBlock * llvmBasicBlock) = 0;
	};

} // namespace take2
} // namespace omni

#endif // include guard
