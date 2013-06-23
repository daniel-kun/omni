#include <omni/core/function.hpp>
#include <omni/core/module.hpp>
#include <llvm/Function.h>
#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>

/**
Implementation details for function
**/
class omni::core::function_impl {
public:
    function_impl (module & module) :
        _module (module)
    {
    }

    module                         & _module;
    std::shared_ptr <llvm::Function> _llvmFunction;
};

// Implementation of omni::core::function

omni::core::function::function (omni::core::module & module, std::string const & name) :
    _impl (new function_impl (module))
{
    llvm::Module & llvmMod (_impl->_module.getLLVMModule ());
    llvm::Type * voidType = llvm::Type::getVoidTy (llvmMod.getContext ());
    auto function = llvmMod.getOrInsertFunction (name, voidType, NULL);
    _impl->_llvmFunction.reset (llvm::cast <llvm::Function> (function));
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

