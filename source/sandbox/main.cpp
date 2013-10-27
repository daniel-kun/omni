#include "clang_sandbox.hpp"
#include <omni/take2/sandbox.hpp>
#include <omni/take2/context.hpp>
#include <omni/take2/type.hpp>
#include <omni/take2/type_class.hpp>
#include <omni/take2/builtin_literal.hpp>
#include <omni/take2/literal_expression.hpp>
#include <omni/take2/binary_operator_expression.hpp>
#include <omni/take2/block.hpp>
#include <omni/take2/return_statement.hpp>
#include <omni/take2/function.hpp>
#include <iostream>
#include <string>

extern "C" { // Declarations for functions defined in .ll-code
void template_basic ();
int test();
}

void sandbox_take2 ()
{
    using namespace omni::take2;

    context c;
    std::shared_ptr <type> signedIntType (new type (c, type_class::t_signedInt));
    std::shared_ptr <literal> leftLiteral (new builtin_literal <int> (c, 10));
    std::shared_ptr <literal> rightLiteral (new builtin_literal <int> (c, 9));
    std::shared_ptr <literal_expression> leftOperand (new literal_expression (leftLiteral));
    std::shared_ptr <literal_expression> rightOperand (new literal_expression (rightLiteral));
    std::shared_ptr <binary_operator_expression> sandboxExpression (new binary_operator_expression (
            binary_operator_expression::binary_operation::binary_plus_operation,
            leftOperand,
            rightOperand));

    std::shared_ptr <block> mainBody (new block ());
//    std::shared_ptr <expression_statement> sandboxStatement (new expression_statement (sandboxExpression));
//    mainBody->appendStatement (sandboxStatement);
    std::shared_ptr <return_statement> returnStatement (new return_statement (sandboxExpression));
    mainBody->appendStatement (returnStatement);
    std::shared_ptr <type> mainReturnType (new type (c, type_class::t_signedInt));
    std::shared_ptr <function> main (new function ("test", mainReturnType, mainBody));
    c.addFunction (main);
    //c.setEntryPoint (main);
    c.emitAssemblyFile ("C:/temp/test.ll");

    /*
    llvm::LLVMContext & llvmContext = llvm::getGlobalContext();
    llvm::Module * module = new llvm::Module ("test", llvmContext);
    llvm::Function * func = llvm::cast <llvm::Function> (module->getOrInsertFunction ("test", llvm::IntegerType::get (llvmContext, 32), nullptr));
    func->setCallingConv (llvm::CallingConv::C);
    llvm::BasicBlock * funcBody = llvm::BasicBlock::Create (llvmContext, "", func);
    llvm::IRBuilder <> builder (funcBody);
    llvm::Value * op = builder.CreateBinOp (
        llvm::Instruction::BinaryOps::Add,
        llvm::ConstantInt::get (llvm::IntegerType::get (llvmContext, 32), 10),
        llvm::ConstantInt::get (llvm::IntegerType::get (llvmContext, 32), 9));
    builder.CreateRet (op);

    llvm::verifyModule (* module, llvm::PrintMessageAction);

    llvm::PassManager pm;
    pm.add(llvm::createPrintModulePass(& llvm::outs()));
    pm.run(* module);
    delete module;
    */
}


int main (int argc, char * argv[])
{
    //template_basic ();
    //clang_sandbox ();
    try {
	    sandbox_take2 ();
    } catch (std::exception const & e) {
        std::cerr << e.what () << std::endl;
    }

	std::cout << "Finished!" << std::endl;
    std::string line;
    std::getline (std::cin, line);

    return 0;
}