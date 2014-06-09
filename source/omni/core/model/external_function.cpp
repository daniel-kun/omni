#include <omni/core/model/external_function.hpp>
#include <omni/core/model/module.hpp>
#include <omni/core/model/type.hpp>
#include <omni/core/model/parameter.hpp>

#include <llvm/IR/Function.h>

/**
@brief Initializes an external_function with the given libraryName, functionName, returnType, parameters and flag whether the function is imported from a dll (isDllImport).

@param libraryName The name of the library that the function is defined in. Can be an empty string, when the library is somehow linked by other means (e.g. 
by other functions that use that library or by module_emit_options::addLibrary()). Can be changed later with setLibraryName().
@param functionName The name of the function. If it is a C++ function, this is the mangled name. Can be changed later with entity::setName ().
@param returnType The returnType of the function. Can be changed later with function_prototype::setReturnType ().
@param parameters A list of parameters that this function takes, if any. Can be an empty vector. Can be changed later with setParameters() or appendParameter ().
@param isDllImport True, if this function is imported from a DLL. Only for Windows. Can be changed later with setDllImport().
**/
omni::core::model::external_function::external_function (std::string libraryName,
                                                         std::string functionName,
                                                         std::shared_ptr <model::type> returnType,
                                                         std::vector <std::shared_ptr <parameter>> parameters,
                                                         bool isDllImport) :
    function_prototype (functionName, returnType, parameters),
    _llvmFunction (),
    _libraryName (libraryName),
    _isDllImport (isDllImport)
{
}

omni::core::domain omni::core::model::external_function::getDomain () const
{
    return domain::external_function;
}

/**
@brief Sets the libraryName that specifies which library this external_function will be imported from.
@param libraryName The name of the library that this external_function will be imoported from. I.e. "foo.so" or "foo.a" on Linux, or "foo.dll" or "foo.lib" on Windows.
If this function is imported from a DLL, you need to setDllImport () to true.
@see getLibraryName
**/
void omni::core::model::external_function::setLibraryName (std::string libraryName)
{
    _libraryName = libraryName;
}

/**
@brief Returns the name of the library that this external function is defined in.

The library will automatically be added to the linker when a shared library is emitted (@see module::emitSharedLibraryFile).

@return The name of the libary that this external function is defined in.
@see setLibraryName
**/
std::string omni::core::model::external_function::getLibraryName () const
{
    return _libraryName;
}

/**
@brief Changes whether this function is imported from a DLL. Only used on Windows.
@param isDllImport If set to true, this function will be imported from a dll. If set to false, this function will be imported from a static library (.lib).
@see isDllImport
**/
void omni::core::model::external_function::setDllImport (bool isDllImport)
{
    _isDllImport = isDllImport;
}

/**
@brief Returns true if this function is imported from a DLL. Only used for Windows.
@return True, if this function is imported from a DLL. False, if this function is imported from a static library (.lib).
@see setDllImport
**/
bool omni::core::model::external_function::isDllImport () const
{
    return _isDllImport;
}

void omni::core::model::external_function::fillLibraries (std::set <std::string> & libraries)
{
    if (libraries.find (_libraryName) == libraries.end ())
        libraries.insert (_libraryName);
}

/*
Internal.

Returns an llvm::Function in the module currently returned by getModule () with the same characteristics as this function
and with llvm::Function::ExternalLinkage. If isDllImport () currently returns true, the DLLStorageClass of the llvm::Function
is set to DLLImportStorageClass.
*/
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
    return _llvmFunction;
}
