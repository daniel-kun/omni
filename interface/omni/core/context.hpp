#ifndef OMNI_CORE_CONTEXT_HPP
#define OMNI_CORE_CONTEXT_HPP

#include <omni/core/core.hpp>
#include <omni/core/object.hpp>
#include <memory>

// forward declarations
namespace llvm {
class LLVMContext;
}

// class definition

namespace omni {
namespace core {

class context_impl;

/**
**/
class OMNI_CORE_API context : public object {
public:
	context ();

	void save (std::string const & fileName);
	void save (std::ostream & stream);

	llvm::LLVMContext const & getLLVMContext () const;
	llvm::LLVMContext       & getLLVMContext ();

	static std::string generateUuid ();

    static std::string const & getTypeName ();

private:
	std::shared_ptr <context_impl> _impl;
}; // class context

} // namespace core
} // namespace omni

#endif // include guard
