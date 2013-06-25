#include <omni/core/function.hpp>
#include <omni/core/module.hpp>
#include <omni/core/type.hpp>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/DerivedTypes.h>
#include <omni/core/context.hpp>

/**
Implementation details for function
**/
class omni::core::function_impl {
public:
    function_impl (type & type) :
        _type (type)
    {
    }

    type             & _type;
	llvm::Function   * _llvmFunction;
	llvm::BasicBlock * _llvmBody;
};

// Implementation of omni::core::function
/**
Initialises this function for type `type' with the name `name'. This should
only be used internally - to create a new function, use type::addFunction.
**/
omni::core::function::function (omni::core::type & type, std::string const & name) :
    _impl (new function_impl (type))
{
	llvm::LLVMContext & context (_impl->_type.getModule ().getContext ().getLLVMContext ());
    llvm::Module & llvmMod (_impl->_type.getModule ().getLLVMModule ());
	llvm::Type * voidType = llvm::Type::getVoidTy (context);
    auto function = llvmMod.getOrInsertFunction (name, voidType, NULL);
    _impl->_llvmFunction = llvm::cast <llvm::Function> (function);
	_impl->_llvmFunction->setCallingConv (llvm::CallingConv::C);
	_impl->_llvmBody = llvm::BasicBlock::Create (context, llvm::Twine (), _impl->_llvmFunction);
}

/**
Sets the name for this function.
@see getName()
**/
void omni::core::function::setName (std::string const & name)
{
    _impl->_llvmFunction->setName (name);
    onPropertyChanged ("name");
}

/**
Returns the name of this function.
**/
std::string omni::core::function::getName () const
{
    return _impl->_llvmFunction->getName ();
}

std::string const & omni::core::function::getTypeName ()
{
    static std::string result ("function");
    return result;
}
