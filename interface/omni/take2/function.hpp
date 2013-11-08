#ifndef OMNI_TAKE2_FUNCTION_HPP
#define OMNI_TAKE2_FUNCTION_HPP

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

	class OMNI_TAKE2_API function : public context_part {
	public:
        function (std::string const & name, std::shared_ptr <type> returnType, std::shared_ptr <block> body);
        virtual ~ function ();

        const std::shared_ptr <type> getReturnType () const;
        std::shared_ptr <type> getReturnType ();

        linkage_type getLinkageType () const;
        void setLinkageType (linkage_type linkageType);

        llvm::Function * llvmFunction (llvm::Module & llvmModule);

		std::vector <std::shared_ptr <parameter>> getParameters () const; // TODO
		const std::shared_ptr <block> getBody () const;

    private:
        llvm::Function * _llvmFunction;
        linkage_type _linkageType;
        std::shared_ptr <type> _returnType;
        std::shared_ptr <block> _body;
	};

} // namespace take2
} // namespace omni

#endif // include guard
