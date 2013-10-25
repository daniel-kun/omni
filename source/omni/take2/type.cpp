#include <omni/take2/type.hpp>
#include <omni/take2/not_implemented_error.hpp>

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>

omni::take2::type::type (omni::take2::type_class typeClass) :
    _typeClass (typeClass)
{
}

omni::take2::type::~ type ()
{
}

llvm::Type * omni::take2::type::llvmType ()
{
    switch (_typeClass) {
    case type_class::t_signedInt:
        return llvm::IntegerType::get (llvm::getGlobalContext (), 32);
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

