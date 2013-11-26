#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/PassManager.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/ADT/Triple.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#define BOOST_TEST_MODULE OmniTake2
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (llvm)

/*
BOOST_AUTO_TEST_CASE (llvmPlayground)
{
    llvm::LLVMContext c;
    llvm::Module module("test", c);
    llvm::Type * functionType = llvm::IntegerType::get(c, 16);
    llvm::Function * llvmFunction = llvm::cast <llvm::Function>(module.getOrInsertFunction("foo", functionType, nullptr));
    llvmFunction->setCallingConv(llvm::CallingConv::C);
    llvm::BasicBlock * body = llvm::BasicBlock::Create(c, "__entry__", llvmFunction);
    llvm::IRBuilder <> builder(body);
    llvm::Value * result = builder.CreateBinOp(llvm::Instruction::BinaryOps::Add, llvm::ConstantInt::getSigned(functionType, 40), llvm::ConstantInt::getSigned(functionType, 2));
    builder.CreateRet(result);

    llvm::verifyModule(module, llvm::PrintMessageAction);

    std::string errorInfo;
    llvm::raw_fd_ostream fileStream("test.ll", errorInfo);

    llvm::PassManager pm;
    pm.add(llvm::createPrintModulePass(& fileStream));
    pm.run(module);
}
*/

BOOST_AUTO_TEST_SUITE_END ()
