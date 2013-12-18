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

BOOST_AUTO_TEST_SUITE (llvmTests)

/*
BOOST_AUTO_TEST_CASE (llvmPlaygroundExternalFunction)
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
    llvm::raw_fd_ostream fileStream("playgroundPutchar.ll", errorInfo);

    llvm::PassManager pm;
    pm.add(llvm::createPrintModulePass(& fileStream));
    pm.run(module);
}

BOOST_AUTO_TEST_CASE (llvmPlaygroundExternalVariableDeclaration)
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

    // Here is the variable declaration and variable usage:
    llvm::IRBuilder <true, llvm::NoFolder> builder(body);
    // Create a variable on the stack using alloca:
    llvm::AllocaInst * pointerAddress = builder.CreateAlloca (int32Type);
    // Store a value to the variable:
    builder.CreateStore (llvm::ConstantInt::get (int32Type, 'O'), pointerAddress);
    // Load the value of the variable again:
    llvm::Value * loadedValue = builder.CreateLoad (pointerAddress);
    // Call printf with the loaded value:
    std::vector <llvm::Value*> callArguments;
    callArguments.push_back (loadedValue);
    builder.CreateCall (putcharFunction, callArguments);

    builder.CreateRet (llvm::ConstantInt::get (int32Type, 0));

    llvm::verifyModule(module, llvm::PrintMessageAction);

    std::string errorInfo;
    llvm::raw_fd_ostream fileStream("playgroundVariableDeclartion.ll", errorInfo);

    llvm::PassManager pm;
    pm.add(llvm::createPrintModulePass(& fileStream));
    pm.run(module);
}
*/
BOOST_AUTO_TEST_SUITE_END ()
