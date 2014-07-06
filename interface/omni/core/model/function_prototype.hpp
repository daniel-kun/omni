#ifndef OMNI_CORE_MODEL_FUNCTION_PROTOTYPE_HPP
#define OMNI_CORE_MODEL_FUNCTION_PROTOTYPE_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/scope.hpp>

#include <memory>
#include <vector>
#include <string>

namespace llvm {
    class FunctionType;
    class Function;
    class Module;
}

namespace omni {
namespace core {
    class context;
}
}

namespace omni {
namespace core {
namespace model {
    class module;
    class parameter;
    class block;
    class type;

    /**
    @class function_prototype function_prototype.hpp omni/core/model/function_prototype.hpp

    @brief This class is abstract. A function_prototype defines the name, return type and parameters of a function and adds basic functionalities to read and modify these values.

    function_prototype serves as a common divisor for function and external_function, since they share their main characteristics.
    See @see omni::core::model::function and @see external_function for more details.
    **/
    class OMNI_CORE_API function_prototype : public scope {
    public:
        function_prototype (std::string const & name,
                            std::shared_ptr <type> returnType,
                            std::vector <std::shared_ptr <parameter>> parameters = std::vector <std::shared_ptr <parameter>> ());
        virtual ~ function_prototype ();

        void setReturnType (std::shared_ptr <type> returnType);
        const std::shared_ptr <type> getReturnType () const;
        std::shared_ptr <type> getReturnType ();

        llvm::FunctionType * llvmFunctionType ();
        virtual llvm::Function * llvmFunction () = 0;

        void appendParameter (std::shared_ptr <parameter> parameter);
        void setParameters (std::vector <std::shared_ptr <parameter>> parameters);
        std::vector <std::shared_ptr <parameter>> getParameters ();
 
    private:
        std::shared_ptr <type> _returnType;
        std::size_t _paramCount;
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
