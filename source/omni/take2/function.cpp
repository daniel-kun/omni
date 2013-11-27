#include <omni/take2/function.hpp>
#include <omni/take2/context.hpp>
#include <omni/take2/type.hpp>
#include <omni/take2/block.hpp>
#include <omni/take2/statement.hpp>
#include <omni/take2/parameter.hpp>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Module.h>

omni::take2::function::function (std::string const & name,
                                 std::shared_ptr <type> returnType,
                                 std::shared_ptr <block> body) :
    function_prototype (name, returnType),
    _body (body)
{
}


const std::shared_ptr <omni::take2::block> omni::take2::function::getBody () const
{
    return _body;
}

llvm::Function * omni::take2::function::llvmFunction (llvm::Module & llvmModule)
{
    if (_llvmFunction != nullptr) {
        return _llvmFunction;
    } else {
        llvm::Function * _llvmFunction = llvm::cast <llvm::Function> (llvmModule.getOrInsertFunction (getName (), _returnType->llvmType (), nullptr));
        for (auto i : _parameters) {
            llvm::Argument * arg = new llvm::Argument (i->getType ().llvmType ());
            _llvmFunction->getArgumentList ().push_back (arg);
        }
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
