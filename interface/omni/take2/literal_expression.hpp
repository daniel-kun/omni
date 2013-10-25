#ifndef OMNI_TAKE2_LITERAL_EXPRESSION_HPP
#define OMNI_TAKE2_LITERAL_EXPRESSION_HPP

#include <omni/take2/take2.hpp>
#include <omni/take2/expression.hpp>
#include <memory>

namespace omni {
namespace take2 {
    class literal;

	/**
	A literal expression is an expression that simply returns a value that was already defined at compile time.
	**/
	class OMNI_TAKE2_API literal_expression : public expression {
	public:
        literal_expression (std::shared_ptr <literal> literal);

        llvm::Value * llvmValue (llvm::BasicBlock * llvmBasicBlock) override;

    private:
        std::shared_ptr <literal> _literal;
	};

} // namespace take2
} // namespace omni

#endif // include guard
