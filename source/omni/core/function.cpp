#include <omni/core/function.hpp>
#include <omni/core/context.hpp>
#include <omni/core/module.hpp>
#include <omni/core/type.hpp>
#include <omni/core/block.hpp>
#include <omni/core/statement.hpp>
#include <omni/core/parameter.hpp>
#include <omni/core/no_context_error.hpp>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Module.h>

/**
Initializes a function implementation with the given name, returnType, body and visibility.
@param name The name of this function.
@param returnType The return type of this function. Use a type constucted with the type_class omni::core::type_class::t_void for functions that have no return value.
@param body The body (implementation) of this function.
@param isExported Specifies, whether this function is visible from outside the module it is defined in. @see isExported().
**/
omni::core::function::function (module & module,
                                std::string const & name,
                                std::shared_ptr <type> returnType,
                                std::shared_ptr <block> body,
                                bool isExported) :
    function_prototype (module, name, returnType),
    _module (module),
    _body (body),
    _isExported (isExported)
{
}

/**
Returns true, if this function is exported from the module it is defined in. Depending on what kind of module it is, exporting
has different meanings.
If isExported () returns false, the function is only locally visible in the module it is defined in.
**/
bool omni::core::function::isExported () const
{
    return _isExported;
}

/**
Returns the body of this function in a const form.
**/
const std::shared_ptr <omni::core::block> omni::core::function::getBody () const
{
    return _body;
}

/**
Returns the body of this function in a modifyable form.
**/
std::shared_ptr <omni::core::block> omni::core::function::getBody ()
{
    return _body;
}


llvm::Function * omni::core::function::llvmFunction ()
{
    if (getContext () == nullptr) {
        throw no_context_error (omni::core::domain::function, getName ());
    }
    if (_llvmFunction != nullptr) {
        return _llvmFunction;
    } else {
        llvm::FunctionType * funcType = llvmFunctionType ();

        llvm::GlobalValue::LinkageTypes linkageType;
        if (isExported ()) {
            // TODO: Handle static and dynamic libraries differently - if omni will have static libraries, that is.
            linkageType = llvm::GlobalValue::DLLExportLinkage;
        } else {
            linkageType = llvm::GlobalValue::InternalLinkage;
        }
        _llvmFunction = llvm::Function::Create (funcType, linkageType, getName (), & getModule ().llvmModule ());

        llvm::BasicBlock * body = llvm::BasicBlock::Create (getContext ()->llvmContext (), "__entry__", _llvmFunction);
        for (auto i : _body->getStatements ()) {
            i->llvmEmit (body);
        }
        return _llvmFunction;
    }
}
