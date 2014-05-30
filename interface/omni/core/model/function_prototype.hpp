#ifndef OMNI_CORE_FUNCTION_PROTOTYPE_HPP
#define OMNI_CORE_FUNCTION_PROTOTYPE_HPP

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
    A function_prototype defines the name, return type and parameters of a function and adds basic functionalities to read and modify these values.
    **/
    class OMNI_CORE_API function_prototype : public scope {
    public:
        function_prototype (std::string const & name,
                            std::shared_ptr <type> returnType,
                            std::vector <std::shared_ptr <parameter>> parameters = std::vector <std::shared_ptr <parameter>> ());
        virtual ~ function_prototype ();

        const std::shared_ptr <type> getReturnType () const;
        std::shared_ptr <type> getReturnType ();

        llvm::FunctionType * llvmFunctionType ();
        virtual llvm::Function * llvmFunction () = 0;

        void addParameter (std::shared_ptr <parameter> parameter);
        void setParameters (std::vector <std::shared_ptr <parameter>> parameters);
        std::vector <std::shared_ptr <parameter>> getParameters () const;
 
    protected:
        std::shared_ptr <type> _returnType;
        std::size_t _paramCount;
        llvm::Function * _llvmFunction;
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
