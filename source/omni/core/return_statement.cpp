#include <omni/core/return_statement.hpp>
#include <omni/core/expression.hpp>

#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/NoFolder.h>

omni::core::return_statement::return_statement () :
    _expression ()
{
}

omni::core::return_statement::return_statement (std::shared_ptr <expression> expression) :
    _expression (expression)
{
}

llvm::BasicBlock * omni::core::return_statement::llvmEmit (llvm::BasicBlock * llvmBasicBlock)
{
    llvm::IRBuilder <true, llvm::NoFolder> builder (llvmBasicBlock);
    if (_expression.get () == nullptr) {
        builder.CreateRetVoid ();
    } else {
        builder.CreateRet (_expression->llvmValue (llvmBasicBlock));
    }
    return llvmBasicBlock;
}
