#include <omni/core/type.hpp>
#include <omni/core/context.hpp>
#include <omni/core/not_implemented_error.hpp>

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>

omni::core::type::type (context & context, omni::core::type_class typeClass) :
    _typeClass (typeClass)
{
    setContext (& context);
}

omni::core::type::~ type ()
{
}

/**
Returns a shared_ptr for a instance of type for the desired context and type_class.
Short-hand for creating a type with type::sharedBasicType(context, typeClass); with the additional benefit that types are cached in the context.
@see context::sharedBasicType(type_class);
**/
std::shared_ptr <omni::core::type> omni::core::type::sharedBasicType (context & context, type_class typeClass)
{
    return context.sharedBasicType (typeClass);
}


llvm::Type * omni::core::type::llvmType ()
{
    switch (_typeClass) {
    case type_class::t_void:
        return llvm::Type::getVoidTy (getContext ()->llvmContext ());
        break;
    case type_class::t_unsignedInt:
    case type_class::t_signedInt:
        return llvm::Type::getInt32Ty (getContext ()->llvmContext ());
        break;
    case type_class::t_unsignedShort:
    case type_class::t_signedShort:
        return llvm::Type::getInt16Ty (getContext ()->llvmContext ());
        break;
    case type_class::t_unsignedByte:
    case type_class::t_signedByte:
        return llvm::Type::getInt8Ty (getContext ()->llvmContext ());
        break;
    case type_class::t_boolean:
        return llvm::Type::getInt1Ty (getContext ()->llvmContext ());
        break;
    default:
        throw not_implemented_error (__FILE__, __FUNCTION__, __LINE__);
    }
}

omni::core::type_class omni::core::type::getTypeClass ()
{
    return _typeClass;
}

omni::core::type_class const omni::core::type::getTypeClass () const
{
    return _typeClass;
}

