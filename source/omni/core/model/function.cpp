#include <omni/core/model/function.hpp>
#include <omni/core/context.hpp>
#include <omni/core/model/module.hpp>
#include <omni/core/model/type.hpp>
#include <omni/core/model/block.hpp>
#include <omni/core/model/statement.hpp>
#include <omni/core/model/parameter.hpp>
#include <omni/core/no_context_error.hpp>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Module.h>

// See meta_info.cpp for initialization.
namespace omniMetaImpl {
extern omni::core::model::meta_info functionMetaInfo;
}

/**
@brief Initializes a function implementation with the given name, returnType, body, parameters and visibility.

The body's and the parameter's parent will be set to this function.

@param name The name of this function.
@param returnType The return type of this function. Use a type constucted with the type_class omni::core::type_class::t_void for functions that have no return value.
@param body The body (implementation) of this function.
@param parameters An optional list of parameters that the function receives.
@param isExported Specifies, whether this function is visible from outside the module it is defined in. @see isExported().
**/
omni::core::model::function::function (std::string const & name,
                                       std::shared_ptr <type> returnType,
                                       std::shared_ptr <block> body,
                                       std::vector <std::shared_ptr <parameter>> parameters,
                                       bool isExported) :
    function_prototype (name, returnType, parameters),
    _llvmFunction (),
    _isExported (isExported)
{
    setBody (body);
}

omni::core::model::meta_info & omni::core::model::function::getStaticMetaInfo ()
{
    return omniMetaImpl::functionMetaInfo;
}

omni::core::model::meta_info & omni::core::model::function::getMetaInfo () const
{
    return getStaticMetaInfo ();
}

omni::core::domain omni::core::model::function::getDomain () const
{
    return domain::function;
}

/**
@brief Changes whether this function is visible from other modules.
@param isExported Should be set to true, if this function should be exported from this module. Should be set to false, if this function should only be visible locally within the module.
@see isExported
**/
void omni::core::model::function::setExported (bool isExported)
{
    _isExported = isExported;
}

/**
@brief Return whether this function is visible from other modules.

If a function is exported, it will create a visible symbol in an emitted executable file. Only exported functions can be called across module boundaries.
Non-exported functions can only be called from within the same module that the function is defined in.

@return True, if this function is exported from this module. False, if the function is only visible locally within the module.
**/
bool omni::core::model::function::isExported () const
{
    return _isExported;
}

/**
@brief Sets the body of this function.

The body contains the list of statements that are executed when the function is called.

If the function has a non-void return-type, the body must contain a return_statement for every control-flow.
@param body The new body for this function.
**/
void omni::core::model::function::setBody (std::shared_ptr <block> body)
{
    setComponent (domain::block, "body", body);
}

/**
@brief Returs the body of this function.

The body contains the list of statements that are executed when the function is called.

If the function has a non-void return-type, the body must contain a return_statement for every control-flow.

The returned body is const and can not be modified.
@result The body of this function.
**/
const std::shared_ptr <omni::core::model::block> omni::core::model::function::getBody () const
{
    return getComponentAs <block> (domain::block, "body");
}

/**
@brief Returs the body of this function.

The body contains the list of statements that are executed when the function is called.

If the function has a non-void return-type, the body must contain a return_statement for every control-flow.

The returned body can be modified.
@result The body of this function.
**/
std::shared_ptr <omni::core::model::block> omni::core::model::function::getBody ()
{
    return getComponentAs <block> (domain::block, "body");
}

/*
Internal.

Returns an llvm::Function in the module currently returned by getModule () with the same characteristics as this function
and with a BasicBlock as the entry point named __entry__ that contains all statements from the block currently returned by getBody ().

If this function is called subsequently, the llvm::Function will only be created on the first call - all other calls will simply returned
the llvm::Function that was created on the first call.

@return An llvm::Function resembling this omni::core::model::function.
*/
llvm::Function * omni::core::model::function::llvmFunction ()
{
    if (getContext () == nullptr) {
        throw no_context_error (domain::function, getName ());
    }
    if (_llvmFunction != nullptr) {
        return _llvmFunction;
    } else {
        llvm::FunctionType * funcType = llvmFunctionType ();

        llvm::Function::LinkageTypes linkageType;
        if (isExported ()) {
            // TODO: Handle static and dynamic libraries differently - if omni will have static libraries, that is.
            linkageType = llvm::Function::ExternalLinkage;
        } else {
            linkageType = llvm::Function::InternalLinkage;
        }
        _llvmFunction = llvm::Function::Create (funcType, linkageType, getName (), & getModule ()->llvmModule ());
        if (isExported ()) {
            _llvmFunction->setDLLStorageClass (llvm::GlobalValue::DLLExportStorageClass);
        }

        auto mainBlock = llvm::BasicBlock::Create (getContext ()->llvmContext (), "__entry__", _llvmFunction);
        getBody ()->llvmEmitIntoExistingBlock (mainBlock);

        return _llvmFunction;
    }
}
