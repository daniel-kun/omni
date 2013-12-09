//  The Omni Programming Environment
//
// This file is distributed under the MIT Open Source License.
// See LICENSE.MD for details.

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
#include <llvm/Support/NoFolder.h>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (llvm)

/*
BOOST_AUTO_TEST_CASE (llvmPlayground)
{
    llvm::LLVMContext c;
    llvm::Module module("test", c);

    llvm::Type * int32Type = llvm::Type::getInt32Ty (c);
    std::vector <llvm::Type*> putcharArgs (1, int32Type);
    llvm::FunctionType * putcharFunctionType = llvm::FunctionType::get (int32Type, putcharArgs, false);
    llvm::Function * putcharFunction = llvm::cast <llvm::Function> (llvm::Function::Create (putcharFunctionType, llvm::GlobalValue::ExternalLinkage, "putchar", &module));

    llvm::FunctionType * mainFunctionType = llvm::FunctionType::get (int32Type, std::vector <llvm::Type*> (), false);
    llvm::Function * llvmFunction = llvm::cast <llvm::Function> (llvm::Function::Create (mainFunctionType, llvm::GlobalValue::ExternalLinkage, "main", & module));
    llvmFunction->setCallingConv(llvm::CallingConv::C);
    llvm::BasicBlock * body = llvm::BasicBlock::Create(c, "__entry__", llvmFunction);
    llvm::IRBuilder <true, llvm::NoFolder> builder(body);
    std::vector <llvm::Value*> callArguments;
    callArguments.push_back (llvm::ConstantInt::get (int32Type, static_cast <uint64_t> ('O')));
    builder.CreateCall (putcharFunction, callArguments);
    builder.CreateRet (llvm::ConstantInt::get (int32Type, 0));

    llvm::verifyModule(module, llvm::PrintMessageAction);

    std::string errorInfo;
    llvm::raw_fd_ostream fileStream("test.ll", errorInfo);

    llvm::PassManager pm;
    pm.add(llvm::createPrintModulePass(& fileStream));
    pm.run(module);
}
*/

BOOST_AUTO_TEST_SUITE_END ()
