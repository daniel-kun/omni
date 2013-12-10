#ifndef OMNI_TAKE2_FUNCTION_HPP
#define OMNI_TAKE2_FUNCTION_HPP

#include <omni/take2/take2.hpp>
#include <omni/take2/function_prototype.hpp>

#include <memory>

namespace omni {
namespace take2 {

    /**
    An object of type 'function' defines a function. In contrast to a function_prototype or an external_function, a 'function' includes the definition of the
    function's body and is therefore a complete definition of a function.
    Use function_call_expression to access the value returned by a function (if the function is non-void).
    **/
    class OMNI_TAKE2_API function : public function_prototype {
    public:
        function (std::string const & name, std::shared_ptr <type> returnType, std::shared_ptr <block> body, bool isExported = false);

        bool isExported () const;

        const std::shared_ptr <block> getBody () const;

        llvm::Function * llvmFunction (llvm::Module & llvmModule) override;

    private:
        std::shared_ptr <block> _body;
        bool _isExported;
    };

} // namespace take2
} // namespace omni

#endif // include guard
