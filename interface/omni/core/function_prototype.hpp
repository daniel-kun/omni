#ifndef OMNI_CORE_FUNCTION_PROTOTYPE_HPP
#define OMNI_CORE_FUNCTION_PROTOTYPE_HPP

#include <omni/core/core.hpp>
#include <omni/core/context_part.hpp>

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
    class parameter;
    class block;
    class type;

    /**
    A function_prototype defines the name, return type and parameters of a function and adds basic functionalities to read and modify these values.
    **/
    class OMNI_CORE_API function_prototype : public context_part {
    public:
        function_prototype (std::string const & name,
                            std::shared_ptr <type> returnType,
                            std::vector <std::shared_ptr <omni::core::parameter>> parameters = std::vector <std::shared_ptr <omni::core::parameter>> ());
        virtual ~ function_prototype ();

        const std::shared_ptr <type> getReturnType () const;
        std::shared_ptr <type> getReturnType ();

        llvm::FunctionType * llvmFunctionType ();
        virtual llvm::Function * llvmFunction (llvm::Module & llvmModule) = 0;

        void addParameter (std::shared_ptr <parameter> parameter);
        void setParameters (std::vector <std::shared_ptr <omni::core::parameter>> parameters);
        std::vector <std::shared_ptr <parameter>> getParameters () const;
 
    protected:
        llvm::Function * _llvmFunction;
        std::shared_ptr <type> _returnType;
        std::vector <std::shared_ptr <omni::core::parameter>> _parameters;
    };

} // namespace core
} // namespace omni

#endif // include guard
