// Code taken from https://github.com/thomaslee/llvm-demo/blob/master/main.cc
// Stored here for future reference

#include <iostream>

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/TargetSelect.h>

static llvm::Function*
printf_prototype(llvm::LLVMContext& ctx, llvm::Module *mod)
{
    std::vector<llvm::Type*> printf_arg_types;
    printf_arg_types.push_back(llvm::Type::getInt8PtrTy(ctx));

    llvm::FunctionType* printf_type =
        llvm::FunctionType::get(
            llvm::Type::getInt32Ty(ctx), printf_arg_types, true);

    llvm::Function *func = llvm::Function::Create(
                printf_type, llvm::Function::ExternalLinkage,
                llvm::Twine("printf"),
                mod
           );
    func->setCallingConv(llvm::CallingConv::C);
    return func;
}

static llvm::Function*
main_prototype(llvm::LLVMContext& ctx, llvm::Module *mod)
{
    std::vector<llvm::Type*> main_arg_types;

    llvm::FunctionType* main_type =
        llvm::FunctionType::get(
            llvm::Type::getInt32Ty(ctx), main_arg_types, false);

    llvm::Function *func = llvm::Function::Create(
                main_type, llvm::Function::ExternalLinkage,
                llvm::Twine("main"),
                mod
           );
    func->setCallingConv(llvm::CallingConv::C);
    return func;
}

//int main(int argc, char **argv)
int foo ()
{
    //
    // do this, or ExecutionEngine::create() returns null.
    // dependent on the 'jit' config setting in llvm-config...
    //
    llvm::InitializeNativeTarget();

    llvm::LLVMContext& ctx = llvm::getGlobalContext();
    llvm::Module *module = new llvm::Module("example", ctx);
    llvm::IRBuilder<> builder(ctx);

    //
    // extern void printf(const char *fmt, ...);
    //
    llvm::Function *printf_func = printf_prototype(ctx, module);

    //
    // int main(void)
    // {
    llvm::Function *main_func = main_prototype(ctx, module);
    llvm::BasicBlock *block =
        llvm::BasicBlock::Create(ctx, "", main_func, 0);
    builder.SetInsertPoint(block);

    //
    // int32_t temp = 15 + 10;
    //
    llvm::Constant *left = llvm::ConstantInt::get(ctx, llvm::APInt(32, 15));
    llvm::Constant *right = llvm::ConstantInt::get(ctx, llvm::APInt(32, 10));
    llvm::Value *add = builder.CreateAdd(left, right);

    //
    // printf("%d\n", temp);
    //
    llvm::Constant *format_const =
        llvm::ConstantDataArray::getString(ctx, "%d\n");
    llvm::GlobalVariable *var =
        new llvm::GlobalVariable(
            *module, llvm::ArrayType::get(llvm::IntegerType::get(ctx, 8), 4),
            true, llvm::GlobalValue::PrivateLinkage, format_const, ".str");
    llvm::Constant *zero =
        llvm::Constant::getNullValue(llvm::IntegerType::getInt32Ty(ctx));

    std::vector<llvm::Constant*> indices;
    indices.push_back(zero);
    indices.push_back(zero);
    llvm::Constant *var_ref =
        llvm::ConstantExpr::getGetElementPtr(var, indices);

    llvm::CallInst *call = builder.CreateCall2(printf_func, var_ref, add);
    call->setTailCall(false);

    //
    // return 0;
    // }
    //
    builder.CreateRet(zero);

    //
    // Dump out the IR
    //
    module->dump();

    std::cerr << "------------\n";

    //
    // Execute the program
    //
    llvm::ExecutionEngine *engine = llvm::EngineBuilder(module).create();
    engine->runFunction(main_func, std::vector<llvm::GenericValue>());

    std::string line;
    std::getline (std::cin, line);
    return 0;
}
