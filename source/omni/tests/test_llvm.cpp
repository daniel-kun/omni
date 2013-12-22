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
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FormattedStream.h>

#include <boost/test/unit_test.hpp>

namespace {
    void addDllMain (llvm::LLVMContext & c, llvm::Module & module)
    {
        llvm::Type * i32ptr = llvm::Type::getInt32PtrTy (c);
        llvm::Type * i32 = llvm::Type::getInt32Ty (c);
        llvm::Type * i8 = llvm::Type::getInt8Ty (c);

        std::vector <llvm::Type *> params = { i32ptr, i32, i32ptr };
        llvm::FunctionType * ft = llvm::FunctionType::get (i8, params, false);
        llvm::Function * func = llvm::Function::Create (ft, llvm::GlobalValue::DLLExportLinkage, "DllMain", & module);
        func->setCallingConv(llvm::CallingConv::X86_StdCall);
        llvm::BasicBlock * body = llvm::BasicBlock::Create (c, "__entry__", func);
        llvm::IRBuilder <> builder (body);
        builder.CreateRet (llvm::ConstantInt::get (i8, 1));
    }
}

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

// TODO: This test creates a broken COFF obj file:
// See the test whileStatementTests/doWhileStatement
// See http://llvm.org/bugs/show_bug.cgi?id=18308

BOOST_AUTO_TEST_CASE (llvmPlaygroundDoWhile)
{
    using namespace llvm;
    LLVMContext c;
    Module module("test", c);

    Type * int32Type = Type::getInt32Ty (c);

    FunctionType * mainFunctionType = FunctionType::get (int32Type, std::vector <Type*> (), false);
    Function * llvmFunction = cast <Function> (Function::Create (mainFunctionType, GlobalValue::ExternalLinkage, "doWhileStatementTest", & module));
    llvmFunction->setCallingConv(CallingConv::C);
    llvmFunction->setLinkage (GlobalValue::InternalLinkage);
    

    BasicBlock * body = BasicBlock::Create(c, "__entry__", llvmFunction);
    IRBuilder <true, NoFolder> builder(body);
    AllocaInst * variableAddress = builder.CreateAlloca (int32Type);
    builder.CreateStore (ConstantInt::get (int32Type, 1), variableAddress);

    BasicBlock * whileBlock = BasicBlock::Create (c, "", llvmFunction);
    builder.CreateBr (whileBlock);
    BasicBlock * continueBlock = BasicBlock::Create (c, "", llvmFunction);
    IRBuilder <true, NoFolder> continueBuilder (continueBlock);
    continueBuilder.CreateRet (continueBuilder.CreateLoad (variableAddress));
    {
        IRBuilder <true, NoFolder> whileBuilder (whileBlock);
        Value * variableValue = whileBuilder.CreateLoad (variableAddress);
        Value * whileCondition = whileBuilder.CreateICmp (CmpInst::ICMP_SLT, variableValue, ConstantInt::get (int32Type, 10));

        whileBuilder.CreateCondBr (whileCondition, whileBlock, continueBlock);
    }

    Function * mainFunction = cast <Function> (Function::Create (mainFunctionType, GlobalValue::ExternalLinkage, "main", & module));
    mainFunction->setCallingConv(CallingConv::C);
    mainFunction->setLinkage (GlobalValue::DLLExportLinkage);
    BasicBlock * mainBody = BasicBlock::Create (c, "__entry__", mainFunction);
    IRBuilder <true, NoFolder> mainBuilder (mainBody);
    Value * callTestFunction = mainBuilder.CreateCall (llvmFunction);
    mainBuilder.CreateRet (callTestFunction);

    if (verifyModule(module, PrintMessageAction)) {
        throw std::runtime_error ("Verification of module failed");
    }

    std::string errorInfo;

    std::string errors;
    std::string targetTriple = "i686-pc-win32";
    Triple triple = llvm::Triple (targetTriple);
    InitializeAllTargets ();
    InitializeAllTargetMCs();
    InitializeAllAsmPrinters();
    InitializeAllAsmParsers();

    const Target * target = TargetRegistry::lookupTarget ("", triple, errors);
    TargetOptions targetOptions;
    TargetMachine * targetMachine = target->createTargetMachine (targetTriple, std::string (), std::string (), targetOptions);

    PassManager pm;
    raw_fd_ostream stream ("llvmPlaygroundDoWhile.obj", errorInfo);
    formatted_raw_ostream formattedStream (stream);
    if (targetMachine->addPassesToEmitFile (pm, formattedStream, TargetMachine::CGFT_ObjectFile)) {
        throw std::runtime_error ("Failed to emit object file");
    }
    pm.run (module);
    formattedStream.flush ();
}
*/

BOOST_AUTO_TEST_SUITE_END ()
