#include <omni/core/context.hpp>

#include <llvm/IR/LLVMContext.h>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <fstream>

/**
Implementation details for context
**/
class omni::core::context_impl {
public:
	context_impl (llvm::LLVMContext & context) :
		_llvmContext (context)
	{
	}
	llvm::LLVMContext & _llvmContext;
};

// Implementation of omni::core::context

omni::core::context::context () :
	_impl (new context_impl (llvm::getGlobalContext ()))
{
}

void omni::core::context::save (std::string const & fileName)
{
	std::ofstream stream (fileName);
	save (stream);
}

void omni::core::context::save (std::ostream & stream)
{
	// TODO: Save to .ll file
}

llvm::LLVMContext const & omni::core::context::getLLVMContext () const
{
	return _impl->_llvmContext;
}

llvm::LLVMContext & omni::core::context::getLLVMContext ()
{
	return _impl->_llvmContext;
}

std::string omni::core::context::generateUuid ()
{
	/*
	boost::uuids::uuid result = boost::uuids::random_generator () ();
	std::stringstream str;
	str << result;
	return str.str ();
	*/
	return std::string ();
}

std::string const & omni::core::context::getTypeName ()
{
    static std::string const result ("context");
    return result;
}
