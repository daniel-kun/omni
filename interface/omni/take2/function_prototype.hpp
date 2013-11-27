#ifndef OMNI_TAKE2_FUNCTION_PROTOTYPE_HPP
#define OMNI_TAKE2_FUNCTION_PROTOTYPE_HPP

#include <omni/take2/take2.hpp>
#include <omni/take2/context_part.hpp>
#include <omni/take2/linkage_type.hpp>
#include <memory>
#include <vector>
#include <string>

namespace llvm {
    class Function;
    class Module;
}

namespace omni {
namespace take2 {
    class context;
    class parameter;
    class block;
    class type;

    class OMNI_TAKE2_API function_prototype : public context_part {
    public:
        function_prototype (std::string const & name, std::shared_ptr <type> returnType);
        virtual ~ function_prototype ();

        const std::shared_ptr <type> getReturnType () const;
        std::shared_ptr <type> getReturnType ();

        linkage_type getLinkageType () const;
        void setLinkageType (linkage_type linkageType);

        virtual llvm::Function * llvmFunction (llvm::Module & llvmModule) = 0;

        void addParameter (std::shared_ptr <parameter> parameter);
        void setParameters (std::vector <std::shared_ptr <omni::take2::parameter>> parameters);
        std::vector <std::shared_ptr <parameter>> getParameters () const;
 
        const std::shared_ptr <block> getBody () const;

    protected:
        llvm::Function * _llvmFunction;
        linkage_type _linkageType;
        std::shared_ptr <type> _returnType;
        std::vector <std::shared_ptr <omni::take2::parameter>> _parameters;
    };

} // namespace take2
} // namespace omni

#endif // include guard
