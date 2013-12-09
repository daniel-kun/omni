#include <omni/take2/type.hpp>
#include <omni/take2/context.hpp>
#include <omni/take2/not_implemented_error.hpp>

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>

omni::take2::type::type (context & context, omni::take2::type_class typeClass) :
    _typeClass (typeClass)
{
    setContext (& context);
}

omni::take2::type::~ type ()
{
}

/**
Returns a shared_ptr for a instance of type for the desired context and type_class.
Short-hand for creating a type with type::sharedType(context, typeClass); with the additional benefit that types are cached in the context.
@see context::sharedType(type_class);
**/
std::shared_ptr <omni::take2::type> omni::take2::type::sharedType (context & context, type_class typeClass)
{
    return context.sharedType (typeClass);
}


llvm::Type * omni::take2::type::llvmType ()
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

omni::take2::type_class omni::take2::type::getTypeClass ()
{
    return _typeClass;
}

omni::take2::type_class const omni::take2::type::getTypeClass () const
{
    return _typeClass;
}

