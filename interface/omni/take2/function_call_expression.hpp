#ifndef OMNI_TAKE2_FUNCTION_CALL_EXPRESSION_HPP
#define OMNI_TAKE2_FUNCTION_CALL_EXPRESSION_HPP

#include <omni/take2/take2.hpp>
#include <omni/take2/expression.hpp>
#include <memory>

namespace llvm {
    class Value;
    class BasicBlock;
}

namespace omni {
namespace take2 {
    class function;

	/**
	A void function call is a statement, not an expression, because it does not have a result.
	**/
	class OMNI_TAKE2_API function_call_expression : public expression {
	public:
        function_call_expression ();
        function_call_expression (std::shared_ptr <function> func);

        void setFunction (std::shared_ptr <function> func);
        const std::shared_ptr <function> getFunction () const;
        std::shared_ptr <function> getFunction ();

        virtual llvm::Value * llvmValue (llvm::BasicBlock * llvmBasicBlock) override;

    private:
        std::shared_ptr <function> _function;
	};

} // namespace take2
} // namespace omni

#endif // include guard
