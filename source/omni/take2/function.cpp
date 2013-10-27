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
    _returnType (returnType),
    _body (body)
{
}

omni::take2::function::~function ()
{
}

llvm::Function * omni::take2::function::llvmFunction (llvm::Module & llvmModule)
{
    if (_llvmFunction != nullptr) {
        return _llvmFunction;
    } else {
        llvm::Function * _llvmFunction = llvm::cast <llvm::Function> (llvmModule.getOrInsertFunction (getName (), _returnType->llvmType (), nullptr));
        _llvmFunction->setCallingConv (llvm::CallingConv::C);
        llvm::BasicBlock * body = llvm::BasicBlock::Create (getContext ()->llvmContext (), "__entry__", _llvmFunction);
        for (auto i : _body->getStatements ()) {
            i->llvmEmit (body);
        }
        return _llvmFunction;
    }
}
