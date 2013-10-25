#include <omni/take2/context.hpp>
#include <omni/take2/function.hpp>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/PassManager.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/Analysis/Verifier.h>
#include "llvm/Support/raw_ostream.h"

void omni::take2::context::addFunction (std::shared_ptr <omni::take2::function> function)
{
    _functions.push_back (function);
}

void omni::take2::context::removeFunction (std::shared_ptr <omni::take2::function> function)
{
    _functions.erase (std::find (_functions.begin (), _functions.end (), function));
}

void omni::take2::context::setEntryPoint (std::shared_ptr <function> function)
{
    _entryPoint = function;
}

void omni::take2::context::emitAssemblyFile (std::string const & fileName)
{
    llvm::Module * module = new llvm::Module ("test", llvm::getGlobalContext ());
    for (auto f : _functions) {
        function & function = * f;
        function.llvmFunction (module);
    }

    llvm::verifyModule (* module, llvm::PrintMessageAction);

    llvm::PassManager pm;
    pm.add(llvm::createPrintModulePass(& llvm::outs()));
    pm.run(* module);
    delete module;
}
