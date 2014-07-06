#include <omni/tests/test_utils.hpp>
#include <omni/core/model/type.hpp>
#include <omni/core/model/module.hpp>
#include <omni/core/model/block.hpp>
#include <omni/core/model/function.hpp>
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
    model::module & mod (* func->getModule ());
    std::shared_ptr <model::function> caller (new model::function (functionName, returnType, body, std::vector <std::shared_ptr <model::parameter>> (), true));
    mod.addFunction (caller);
    boost::filesystem::path assemblyFileName = testFileManager.getTestFileName (fileBaseName + ".ll");
    mod.emitAssemblyFile (assemblyFileName.string ());
    module_emit_options options;
#ifdef WIN32 
    boost::filesystem::path sharedLibraryName = testFileManager.getTestFileName (fileBaseName + ".dll");
    options.addLibrarySearchPath ((boost::filesystem::initial_path ().parent_path () /= "build") /= "bin");
#else
    boost::filesystem::path sharedLibraryName = testFileManager.getTestFileName (fileBaseName + ".so");
    options.addLibrarySearchPath (boost::filesystem::initial_path ());
#endif
    mod.emitSharedLibraryFile (sharedLibraryName.string (), options);

//    BOOST_CHECK (boost::filesystem::exists(sharedLibraryName));
    return sharedLibraryName;
}

