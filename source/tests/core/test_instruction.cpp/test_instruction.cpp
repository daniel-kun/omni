#include <omni/core/function.hpp>
#include <omni/core/module.hpp>
#include <omni/core/context.hpp>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>

void test_instruction ()
{
	omni::core::context context;
	omni::core::module module (context, "test");
	omni::core::type & classDemo (module.addClass ("demo"));
	omni::core::function & funcDemonstrate(classDemo.addFunction ("demonstrate"));
	omni::core::function & funcMain (classDemo.addFunction ("main"));

    llvm::BasicBlock * body = funcMain.getLLVMBody ();
    llvm::IRBuilder <> builder (body);
//    builder.create

//    body->CreateBinOp (llvm::Instruction::Add, var1, var2);
}
