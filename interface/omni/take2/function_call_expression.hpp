#ifndef OMNI_TAKE2_FUNCTION_CALL_EXPRESSION_HPP
#define OMNI_TAKE2_FUNCTION_CALL_EXPRESSION_HPP

#include <omni/take2/take2.hpp>
#include <omni/take2/expression.hpp>
#include <memory>
#include <vector>

namespace llvm {
    class Value;
    class BasicBlock;
}

namespace omni {
namespace take2 {
    class function;
    class expression;

    /**
    A void function call is a statement, not an expression, because it does not have a result.
    **/
    class OMNI_TAKE2_API function_call_expression : public expression {
    public:
        function_call_expression ();
        function_call_expression (std::shared_ptr <function> func);
        function_call_expression (std::shared_ptr <function> func, std::vector <std::shared_ptr <expression>> parameters);

        void setFunction (std::shared_ptr <function> func);
        const std::shared_ptr <function> getFunction () const;
        std::shared_ptr <function> getFunction ();

        void addParameter (std::shared_ptr <expression> parameter);
        void setParameters (std::vector <std::shared_ptr <expression>> parameters);

        virtual llvm::Value * llvmValue (llvm::BasicBlock * llvmBasicBlock) override;

    private:
        std::shared_ptr <function> _function;
        std::vector <std::shared_ptr <expression>> _parameters;
    };

} // namespace take2
} // namespace omni

#endif // include guard
