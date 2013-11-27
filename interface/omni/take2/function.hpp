#ifndef OMNI_TAKE2_FUNCTION_HPP
#define OMNI_TAKE2_FUNCTION_HPP

#include <omni/take2/take2.hpp>
#include <omni/take2/function_prototype.hpp>
#include <memory>

namespace omni {
namespace take2 {

    class OMNI_TAKE2_API function : public function_prototype {
    public:
        function (std::string const & name, std::shared_ptr <type> returnType, std::shared_ptr <block> body);

        const std::shared_ptr <block> getBody () const;

        llvm::Function * llvmFunction (llvm::Module & llvmModule) override;

    private:
        std::shared_ptr <block> _body;
    };

} // namespace take2
} // namespace omni

#endif // include guard
