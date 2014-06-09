#ifndef OMNI_CORE_MODEL_FUNCTION_HPP
#define OMNI_CORE_MODEL_FUNCTION_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/function_prototype.hpp>

#include <memory>

namespace omni {
namespace core {
namespace model {
    class module;

    /**
    @class function function.hpp omni/core/model/function.hpp
    @brief Defines a function implementation that can be called with a function_call_expression.

    A function consists of a name that should be unique within a scope, a return-type, a number of parameters and a body.
    For more information about the return-type and the parameters, see function_prototype.
    A function can be exported. An exported function is visible from other modules than the one the function is defined in.

    A function is not emitted to a binary if it has not been added to a module via scope::addFunction.
    Currently, only top-level functions that are directly added to a module are supported.
    Functions that are added to any other scope deeper within a module are not emitted.
    **/
    class OMNI_CORE_API function : public function_prototype {
    public:
        function (std::string const & name,
                  std::shared_ptr <type> returnType = std::shared_ptr <type> (),
                  std::shared_ptr <block> body = std::shared_ptr <block> (),
                  std::vector <std::shared_ptr <parameter>> parameters = std::vector <std::shared_ptr <parameter>> (),
                  bool isExported = false);

        domain getDomain () const override;

        void setExported (bool isExported);
        bool isExported () const;

        void setBody (std::shared_ptr <block> body);
        const std::shared_ptr <block> getBody () const;
        std::shared_ptr <block> getBody ();

        llvm::Function * llvmFunction () override;

    private:
        llvm::Function * _llvmFunction;
        bool _isExported;
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
