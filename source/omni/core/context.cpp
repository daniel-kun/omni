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
Short-hand for creating a type with new type (*this, typeClass, indirectionLevel); with the additional benefit that types are cached in this context.
@param typeClass The type class of the desired type. @see type_class
@param indirectionLevel The level of pointer-indirection. This is only for internal usage and for representing types imported from external C code. 
The Omni Language itself does not use types with an indiretionLevel > 0. Instead, "optionals" and "references" are used.
@return A shared instance of type with the specified typeClass and indirectionLevel.
@see type::sharedBasicType(context&, type_class);
**/
std::shared_ptr <omni::core::model::type> omni::core::context::sharedBasicType (model::type_class typeClass, int indirectionLevel)
{
    auto typePair = std::make_pair (typeClass, indirectionLevel);
    std::map <std::pair <model::type_class, int>, std::shared_ptr <model::type>>::iterator result = _sharedBasicTypes.find (typePair);
    if (result == _sharedBasicTypes.end ()) {
        std::shared_ptr <model::type> resultType (new model::type (* this, typeClass, indirectionLevel));
        _sharedBasicTypes [typePair] = resultType;
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

