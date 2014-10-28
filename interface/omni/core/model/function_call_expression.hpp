#ifndef OMNI_CORE_FUNCTION_CALL_EXPRESSION_HPP
#define OMNI_CORE_FUNCTION_CALL_EXPRESSION_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/modifying_expression.hpp>

#include <memory>
#include <vector>

namespace llvm {
    class Value;
    class BasicBlock;
}

namespace omni {
namespace core {
namespace model {
    class function_prototype;
    class expression;
    class type;

    /**
    A void function call is a statement, not an expression, because it does not have a result.
    **/
    class OMNI_CORE_API function_call_expression : public modifying_expression {
    public:
        function_call_expression ();
        function_call_expression (std::shared_ptr <function_prototype> func);
        function_call_expression (std::shared_ptr <function_prototype> func, std::vector <std::shared_ptr <expression>> parameters);

        static meta_info & getStaticMetaInfo ();

        virtual meta_info & getMetaInfo () const;

        domain getDomain () const override;

        std::shared_ptr <type> getType () const override;

        void setFunction (std::shared_ptr <function_prototype> func);
        const std::shared_ptr <function_prototype> getFunction () const;
        std::shared_ptr <function_prototype> getFunction ();

        void appendParameter (std::shared_ptr <expression> parameter);
        void setParameters (std::vector <std::shared_ptr <expression>> parameters);
        std::vector <std::shared_ptr <expression>> getParameters ();

        statement_emit_result llvmEmit (llvm::BasicBlock * llvmBasicBlock) override;

    private:
        std::shared_ptr <function_prototype> _function;
        std::size_t _paramCount;
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
