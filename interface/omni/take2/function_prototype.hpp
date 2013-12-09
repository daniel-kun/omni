#ifndef OMNI_TAKE2_FUNCTION_PROTOTYPE_HPP
#define OMNI_TAKE2_FUNCTION_PROTOTYPE_HPP

#include <omni/take2/take2.hpp>
#include <omni/take2/context_part.hpp>
#include <omni/take2/linkage_type.hpp>
#include <memory>
#include <vector>
#include <string>

namespace llvm {
    class FunctionType;
    class Function;
    class Module;
}

namespace omni {
namespace take2 {
    class context;
    class parameter;
    class block;
    class type;

    /**
    A function_prototype defines the name, return type and parameters of a function and adds basic functionalities to read and modify these values.
    **/
    class OMNI_TAKE2_API function_prototype : public context_part {
    public:
        function_prototype (std::string const & name,
                            std::shared_ptr <type> returnType,
                            std::vector <std::shared_ptr <omni::take2::parameter>> parameters = std::vector <std::shared_ptr <omni::take2::parameter>> ());
        virtual ~ function_prototype ();

        const std::shared_ptr <type> getReturnType () const;
        std::shared_ptr <type> getReturnType ();

        llvm::FunctionType * llvmFunctionType ();
        virtual llvm::Function * llvmFunction (llvm::Module & llvmModule) = 0;

        void addParameter (std::shared_ptr <parameter> parameter);
        void setParameters (std::vector <std::shared_ptr <omni::take2::parameter>> parameters);
        std::vector <std::shared_ptr <parameter>> getParameters () const;
 
    protected:
        llvm::Function * _llvmFunction;
        std::shared_ptr <type> _returnType;
        std::vector <std::shared_ptr <omni::take2::parameter>> _parameters;
    };

} // namespace take2
} // namespace omni

#endif // include guard
