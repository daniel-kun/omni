#ifndef OMNI_TAKE2_EXPRESSION_HPP
#define OMNI_TAKE2_EXPRESSION_HPP

#include <omni/take2/take2.hpp>

namespace llvm {
    class BasicBlock;
    class Value;
}

namespace omni {
namespace take2 {

	/**
	An expression is something that returns or is a value. An expression can be a statement, when it's wrapped in an expression_statement
	or it can be part of other statements. For example, the binary_operator_expression has one expression as the left hand side operand and
	another expression as the right hand side operand.
	**/
	class OMNI_TAKE2_API expression {
	public:
		virtual ~ expression () = 0;

        virtual llvm::Value * llvmValue (llvm::BasicBlock * llvmBasicBlock) = 0;
	};

} // namespace take2
} // namespace omni

#endif // include guard
