#include <omni/core/module.hpp>
#include <omni/core/context.hpp>
#include <llvm/IR/Module.h>
#include <string>

/**
Implementation details for module
**/
class omni::core::module_impl {
public:
	module_impl (context & context) :
		_context (context)
	{
	}

	context                      & _context;
	std::list <type>               _types;
	std::shared_ptr <llvm::Module> _llvmModule;
};

// Implementation of omni::core::module

/**
Initialises this object as a new module in the context `context' without a name.
**/
omni::core::module::module (omni::core::context & context) :
	_impl (new module_impl (context))
{
	_impl->_llvmModule.reset (new llvm::Module (std::string (), context.getLLVMContext ()));
}

/**
Initialises this object as a new module in the context `context' with the name `name'.
**/
omni::core::module::module (omni::core::context & context, std::string const & name) :
	_impl (new module_impl (context))
{
	_impl->_llvmModule.reset (new llvm::Module (name, context.getLLVMContext ()));
}

/**
Returns the context this module resides in.
**/
omni::core::context const & omni::core::module::getContext () const
{
	return _impl->_context;
}

/**
Returns the context this module resides in.
**/
omni::core::context & omni::core::module::getContext ()
{
	return _impl->_context;
}

/**
Adds a new class named `name' to this module and returns the newly created type object.
The type object will be of type types::Class.
**/
omni::core::type & omni::core::module::addClass (std::string const & name)
{
	_impl->_types.push_back (type (* this, name));
	return _impl->_types.back ();
}

/**
Returns a begin-iterator for the types in this module.
**/
omni::core::module::TypeIt omni::core::module::typesBegin ()
{
	return _impl->_types.begin ();
}

/**
Returns a begin-iterator for the types in this module.
**/
omni::core::module::TypeIt omni::core::module::typesBegin () const
{
	return _impl->_types.begin ();
}

/**
Returns an end-iterator for the types in this module.
**/
omni::core::module::TypeIt omni::core::module::typesEnd ()
{
	return _impl->_types.end ();
}

/**
Returns an end-iterator for the types in this module.
**/
omni::core::module::TypeIt omni::core::module::typesEnd () const
{
	return _impl->_types.end ();
}

/**
Returns the low-level LLVMModule for this module.
**/
llvm::Module & omni::core::module::getLLVMModule ()
{
	return * _impl->_llvmModule;
}

/**
Returns the low-level LLVMModule for this module.
**/
llvm::Module const & omni::core::module::getLLVMModule () const
{
	return * _impl->_llvmModule;
}

std::string const & omni::core::module::getTypeName ()
{
	static std::string const result ("module");
	return result;
}

