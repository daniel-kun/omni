#include <omni/core/model/external_function.hpp>
#include <omni/core/model/module.hpp>
#include <omni/core/model/type.hpp>
#include <omni/core/model/parameter.hpp>

#include <llvm/IR/Function.h>

/**
Initialises an external_function from a C or C++ library.
@param libraryName The name of the library that the function is defined in. Can be an empty string, when the library is somehow linked by other means (e.g. 
by other functions that use that library or by module_emit_options::addLibrary()).
@param functionName The name of the function. If it is a C++ function, this is the mangled name.
@param returnType The returnType of the function.
@param parameters A list of parameters that this function takes, if any. Can be an empty vector.
@param isDllImport True, if this function is imported from a DLL. Only for Windows.
**/
omni::core::model::external_function::external_function (std::string libraryName,
                                                         std::string functionName,
                                                         std::shared_ptr <model::type> returnType,
                                                         std::vector <std::shared_ptr <parameter>> parameters,
                                                         bool isDllImport) :
    function_prototype (functionName, returnType, parameters),
    _libraryName (libraryName),
    _isDllImport (isDllImport)
{
}

omni::core::domain omni::core::model::external_function::getDomain () const
{
    return domain::external_function;
}

/**
Returns the library that this external function is defined in. The value has been passed in the constructor.
The library will automatically be added to the linker when a shared library is emitted (@see context::emitSharedLibraryFile).
**/
std::string omni::core::model::external_function::getLibraryName () const
{
    return _libraryName;
}

/**
Returns true if this function is imported from a DLL. Only used for Windows.
**/
bool omni::core::model::external_function::isDllImport () const
{
    return _isDllImport;
}

llvm::Function * omni::core::model::external_function::llvmFunction ()
{
    if (_llvmFunction == nullptr) {
        _llvmFunction = llvm::Function::Create (
            llvmFunctionType (),
            llvm::Function::ExternalLinkage,
            getName (),
            & getModule ()->llvmModule ());
        if (_isDllImport) {
            _llvmFunction->setDLLStorageClass (llvm::GlobalValue::DLLImportStorageClass);
        }
    }
    assert (_llvmFunction != nullptr);
    return _llvmFunction;
}

void omni::core::model::external_function::fillLibraries (std::set <std::string> & libraries)
{
    if (libraries.find (_libraryName) == libraries.end ())
        libraries.insert (_libraryName);
}
