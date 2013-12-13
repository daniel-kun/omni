#include <omni/core/context.hpp>
#include <omni/core/type.hpp>

#include <llvm/IR/LLVMContext.h>

omni::core::context::context () :
    _llvmContext (new llvm::LLVMContext ()),
    _sharedBasicTypes (),
    _modules ()
{
}

/**
A destructor must be explicitly defined, because llvm::LLVMContext is an incomplete type to users of omni/core/context.hpp. Without an explicit
dtor, the compiler will try to generate a dtor in whichever place omni::core::context is used. In those places, most likely llvm::LLVMContext is an
incomplete type (because it is only forward-declared) and hence it leads to a compiler error.
So even if this dtor is non-virtual an empty, don't remove it.
**/
omni::core::context::~ context()
{
}

/**
Returns a shared_ptr for a instance of type for the desired context and type_class.
Short-hand for creating a type with type::sharedBasicType(*this, typeClass); with the additional benefit that types are cached in this context.
@see type::sharedBasicType(context&, type_class);
**/
std::shared_ptr <omni::core::type> omni::core::context::sharedBasicType (type_class typeClass)
{
    std::map <type_class, std::shared_ptr <type>>::iterator result = _sharedBasicTypes.find (typeClass);
    if (result == _sharedBasicTypes.end ()) {
        std::shared_ptr <omni::core::type> resultType (new omni::core::type (* this, typeClass));
        _sharedBasicTypes [typeClass] = resultType;
        return resultType;
    }
    return result->second;
}

const llvm::LLVMContext & omni::core::context::llvmContext () const
{
    return * _llvmContext;
}

llvm::LLVMContext & omni::core::context::llvmContext ()
{
    return * _llvmContext;
}

