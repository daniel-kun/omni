#include <omni/take2/function.hpp>
#include <omni/take2/type.hpp>
#include <omni/take2/block.hpp>
#include <omni/take2/statement.hpp>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Module.h>

omni::take2::function::function (context & context,
                                 std::string const & name,
                                 std::shared_ptr <type> returnType,
                                 std::shared_ptr <block> body) :
    context_part (name),
    _context (context),
    _returnType (returnType),
    _body (body)
{
}

omni::take2::function::~function ()
{
}

llvm::Function * omni::take2::function::llvmFunction (llvm::Module & llvmModule)
{
    llvm::Function * result = llvm::cast <llvm::Function> (llvmModule.getOrInsertFunction (getName (), _returnType->llvmType (), nullptr));
    result->setCallingConv (llvm::CallingConv::C);
    llvm::BasicBlock * body = llvm::BasicBlock::Create (llvm::getGlobalContext (), "__entry__", result);
    for (auto i : _body->getStatements ()) {
        i->llvmEmit (body);
    }
    return result;
}
