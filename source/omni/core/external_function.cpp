#include <omni/core/external_function.hpp>
#include <omni/core/type.hpp>
#include <omni/core/module.hpp>
#include <omni/core/parameter.hpp>

#include <llvm/IR/Function.h>

/**
Initialises an external_function from a C or C++ library.
@param libraryName The name of the library that the function is defined in.
@param functionName The name of the function. If it is a C++ function, this is the mangled name.
@param returnType The returnType of the function.
@param parameters A list of parameters that this function takes, if any. Can be an empty vector.
@param isDllImport True, if this function is imported from a DLL. Only for Windows.
**/
omni::core::external_function::external_function (module & module,
                                                  std::string libraryName,
                                                  std::string functionName,
                                                  std::shared_ptr <omni::core::type> returnType,
                                                  std::vector <std::shared_ptr <omni::core::parameter>> parameters,
                                                  bool isDllImport) :
    function_prototype (module, functionName, returnType, parameters),
    _libraryName (libraryName),
    _isDllImport (isDllImport)
{
}

/**
Returns the library that this external function is defined in. The value has been passed in the constructor.
The library will automatically be added to the linker when a shared library is emitted (@see context::emitSharedLibraryFile).
**/
std::string omni::core::external_function::getLibraryName () const
{
    return _libraryName;
}

/**
Returns true if this function is imported from a DLL. Only used for Windows.
**/
bool omni::core::external_function::isDllImport () const
{
    return _isDllImport;
}

llvm::Function * omni::core::external_function::llvmFunction ()
{
    if (_llvmFunction == nullptr) {
        llvm::FunctionType * funcType = llvmFunctionType ();
        llvm::GlobalValue::LinkageTypes linkageType;
        if (_isDllImport) {
            linkageType = llvm::GlobalValue::DLLImportLinkage;
        } else {
            linkageType = llvm::GlobalValue::ExternalLinkage;
        }
        _llvmFunction = llvm::Function::Create (funcType, linkageType, getName (), & getModule ().llvmModule ());
    }
    assert (_llvmFunction != nullptr);
    return _llvmFunction;
}

void omni::core::external_function::fillLibraries (std::set <std::string> & libraries)
{
    if (libraries.find (_libraryName) == libraries.end ())
        libraries.insert (_libraryName);
}
