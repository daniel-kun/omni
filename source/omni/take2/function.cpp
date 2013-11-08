#include <omni/take2/function.hpp>
#include <omni/take2/context.hpp>
#include <omni/take2/type.hpp>
#include <omni/take2/block.hpp>
#include <omni/take2/statement.hpp>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Module.h>

omni::take2::function::function (std::string const & name,
                                 std::shared_ptr <type> returnType,
                                 std::shared_ptr <block> body) :
    context_part (name),
    _llvmFunction (nullptr),
    _linkageType (linkage_type::internal),
    _returnType (returnType),
    _body (body)
{
}

omni::take2::function::~function ()
{
}

/**
Returns the type that this function returns when it is called at runtime.
**/
const std::shared_ptr <omni::take2::type> omni::take2::function::getReturnType () const
{
    return _returnType;
}

/**
Returns the type that this function returns when it is called at runtime.
**/
std::shared_ptr <omni::take2::type> omni::take2::function::getReturnType ()
{
    return _returnType;
}


omni::take2::linkage_type omni::take2::function::getLinkageType () const
{
    return _linkageType;
}

void omni::take2::function::setLinkageType (omni::take2::linkage_type linkageType)
{          
    _linkageType = linkageType;
}


llvm::Function * omni::take2::function::llvmFunction (llvm::Module & llvmModule)
{
    if (_llvmFunction != nullptr) {
        return _llvmFunction;
    } else {
        llvm::Function * _llvmFunction = llvm::cast <llvm::Function> (llvmModule.getOrInsertFunction (getName (), _returnType->llvmType (), nullptr));
        _llvmFunction->setCallingConv (llvm::CallingConv::C);
        switch (getLinkageType ()) {
        case linkage_type::internal:
            _llvmFunction->setLinkage (llvm::GlobalValue::LinkageTypes::InternalLinkage);
            break;
        case linkage_type::external:
            _llvmFunction->setLinkage (llvm::GlobalValue::LinkageTypes::DLLExportLinkage);
            break;
        default:
            break;
        }
        llvm::BasicBlock * body = llvm::BasicBlock::Create (getContext ()->llvmContext (), "__entry__", _llvmFunction);
        for (auto i : _body->getStatements ()) {
            i->llvmEmit (body);
        }
        return _llvmFunction;
    }
}
