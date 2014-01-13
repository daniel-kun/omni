#include <omni/tests/test_utils.hpp>
#include <omni/core/type.hpp>
#include <omni/core/module.hpp>
#include <omni/core/block.hpp>
#include <omni/core/function.hpp>
#include <omni/core/context.hpp>
#include <omni/core/module_emit_options.hpp>
#include <sstream>

/**
Emits a shared library file with the name fileBaseName.dll. The library exports a function "main" that calls the
function `func'. That way, it does not matter whether func is external or not.
Main automatically has the same return type as func. func and main may not take parameters.
@return The path of the created shared library file.
**/
boost::filesystem::path omni::tests::emitSharedLibraryWithFunction (std::shared_ptr <omni::core::model::function> func,
                                                                    omni::tests::test_file_manager & testFileManager,
                                                                    std::string const & fileBaseName,
                                                                    std::string & functionName)
{
    static unsigned int counter = 0;
    using namespace omni::core;
    // First, add a function that calls the wanted function.
    std::shared_ptr <model::type> returnType  (func->getReturnType ());
    std::shared_ptr <model::block> body (new model::block ());
    std::shared_ptr <model::expression> callExpression (new model::function_call_expression (func));
    std::shared_ptr <model::statement> returnStatement (new model::return_statement (callExpression));
    body->appendStatement (returnStatement);
    std::stringstream functionNameBuilder;
    functionNameBuilder << "main" << (++ counter);
    functionName = functionNameBuilder.str ();
    module & mod (func->getModule ());
    std::shared_ptr <model::function> caller (new model::function (mod, functionName, returnType, body, true));
    mod.addFunction (caller);
    boost::filesystem::path sharedLibraryName = testFileManager.getTestFileName (fileBaseName + ".dll");
    boost::filesystem::path assemblyFileName = testFileManager.getTestFileName (fileBaseName + ".ll");
    mod.emitAssemblyFile (assemblyFileName.string ());
    module_emit_options options;
    options.addLibrarySearchPath (boost::filesystem::initial_path () /= "bin");
    mod.emitSharedLibraryFile (sharedLibraryName.string (), options);

//    BOOST_CHECK (boost::filesystem::exists(sharedLibraryName));
    return sharedLibraryName;
}

