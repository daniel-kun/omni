#ifndef OMNI_CORE_MODULE_HPP
#define OMNI_CORE_MODULE_HPP

#include <omni/core/core.hpp>
#include <omni/core/object.hpp>
#include <omni/core/type.hpp>
#include <string>
#include <list>
#include <memory>

// forward declarations
namespace llvm {
class Module;
}

// class definition

namespace omni {
namespace core {

class function;
class context;
class module_impl;

/**
**/
class OMNI_CORE_API module : public omni::core::object {
public:
	typedef std::list <type>::iterator TypeIt;

			  module (context & context);
			  module (context & context, std::string const & name);

	context const & getContext () const;
	context       & getContext ();

	type & addClass (std::string const & name);

	TypeIt typesBegin ();
	TypeIt typesBegin () const;
	TypeIt typesEnd ();
	TypeIt typesEnd () const;

	llvm::Module       & getLLVMModule ();
	llvm::Module const & getLLVMModule () const;

	// Minimal RTTI implementation
	static std::string const & getTypeName ();

private:
	std::shared_ptr <module_impl> _impl;
}; // class module 

} // namespace core
} // namespace omni

#endif // include guard
