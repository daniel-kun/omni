#include <omni/core/module.hpp>
#include <omni/core/context.hpp>
#include <omni/core/function.hpp>
#include <omni/core/block.hpp>
#include <omni/core/logic_error.hpp>
#include <omni/core/already_exists_error.hpp>

#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/PassManager.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>

#include <boost/format.hpp>
#include <boost/filesystem.hpp>

#include <sstream>

namespace {
    /**
    Adds a function with the prototype "dllexport x86_stdcallcc i8 @DllMain(i32*, i32, i32*)" if such a function does not already exist.
    TODO: Implement this in omni instead of llvm.
    **/
    void addDllMainIfMissing (omni::core::context & c, llvm::Module & module)
    {
        llvm::Type * i32ptr = llvm::Type::getInt32PtrTy (c.llvmContext ());
        llvm::Type * i32 = llvm::Type::getInt32Ty (c.llvmContext ());
        llvm::Type * i8 = llvm::Type::getInt8Ty (c.llvmContext ());

        std::vector <llvm::Type *> params = { i32ptr, i32, i32ptr };
        llvm::FunctionType * ft = llvm::FunctionType::get (i8, params, false);
        llvm::Function * func = llvm::Function::Create (ft, llvm::GlobalValue::DLLExportLinkage, "DllMain", & module);
        func->setCallingConv(llvm::CallingConv::X86_StdCall);
        llvm::BasicBlock * body = llvm::BasicBlock::Create (c.llvmContext (), "__entry__", func);
        llvm::IRBuilder <> builder (body);
        builder.CreateRet (llvm::ConstantInt::get (i8, 1));
    }
}

/**
Initializes this module in the context `context' with the name `name'. A new, random id will be assigned to this module.
**/
omni::core::module::module (omni::core::context & context, std::string name) :
    _llvmModule (),
    _context (context),
    _id (),
    _name (name),
    _entryPoint (),
    _parts ()
{
}

/**
Initializes this existing module in the given context and the given name and moduleId.
**/
omni::core::module::module (context & context, id moduleId, std::string name) :
    _llvmModule (),
    _context (context),
    _id (moduleId),
    _name (name),
    _entryPoint (),
    _parts ()
{
}

/**
Returns the context that this module is defined in.
**/
omni::core::context & omni::core::module::getContext ()
{
    return _context;
}

/**
Returns the context that this module is defined in.
**/
const omni::core::context & omni::core::module::getContext () const
{
    return _context;
}

/**
Finds any part of this context by it's unique id. The part has to be added to this context before it can be found.
This happens when the part is created using one of the create...-functions or the part has been added via one of the add...-functions.
@param id The id of the part that should be returned. This should not be an invalid id.
@return The part with the id, if such has been added to the context. A null-shared_ptr is returned, if no such part exists in this context.
**/
std::shared_ptr <omni::core::context_part> omni::core::module::findPartById (omni::core::id id)
{
    id_to_parts_map & m (_parts [id.getDomain ()]);
    id_to_parts_map::iterator i = m.find (id.getId ());
    if (i != m.end ()) {
        return i->second;
    } else {
        return std::shared_ptr <context_part> ();
    }
}

/**
Create a new, unique id for the domain `domain'.
@param domain The domain that the id should be valid for.
@return A new, unique id that can be used to identify newly created parts for this context.
**/
omni::core::id omni::core::module::createId (omni::core::domain domain)
{         
    static unsigned int counter = 0;
    //static boost::uuids::random_generator generator;
    std::string strId;
    do {
        //boost::uuids::uuid uuid = generator ();
        std::stringstream str;
        str << ++ counter;
        //strId = boost::lexical_cast <std::string> (uuid);
        strId = str.str ();
    } while (findPartById (id (domain, strId)).get () != nullptr);
    return id (domain, strId);
}

/**
Creates a new function object for the function with the name `name', adds it to this module and returns it.
Calling createFunction is the same as creating a new function with this module as the first paramter and then calling addFunction().
That's why this function will automatically be assigned a new id.
@param name The name of the function. There may not be a function with the same name in the context, otherwise an already_exits_error exception will be thrown.
@param returnType The type that the function returns.
@param body The body of the function.
@exception already_exists_error Is thrown when a function with the name `name' already exists in this context.
**/
std::shared_ptr <omni::core::function> omni::core::module::createFunction (std::string const & name, std::shared_ptr <type> returnType, std::shared_ptr <block> body)
{
    std::shared_ptr <function> result (new function (* this, name, returnType, body));
    addFunction (result);
    return result;
}

/**
Adds the function `function' to this context, if there is not already another function with the same name.
`function' will automatically be assigned a new id before it is added to this context.
@param function The function that should be added to this context.
@exception already_exists_error Is thrown when a function with the same name as `function's name already exists in this context.
**/
void omni::core::module::addFunction (std::shared_ptr <omni::core::function_prototype> function)
{
    std::shared_ptr <omni::core::function_prototype> func = findFunctionByName (function->getName ());
    if (func.get () != nullptr) {
        throw already_exists_error (domain::function, function->getName ());
    }
    function->setContext (& _context);
    id newFunctionId = createId (domain::function);
    function->setId (newFunctionId);
    id_to_parts_map & functionMap (_parts [domain::function]);
    functionMap [newFunctionId.getId ()] = function;
}

/**
Returns the function with the name `name', if such a function is part of this context.
Only functions that were created using createFunction or were added via addFunction are part of this context.
@param The name of the function that should be returned. Should not be empty.
@return The function with the name `name' that has previously been added to this context.
**/
std::shared_ptr <omni::core::function_prototype> omni::core::module::findFunctionByName (std::string const & name)
{
    id_to_parts_map & functionMap (_parts [domain::function]);
    auto found = std::find_if (functionMap.begin (), functionMap.end (), [name] (std::pair <std::string, std::shared_ptr <context_part>> f) -> bool {
        return f.second->getName () == name;
    });
    if (found != functionMap.end ()) {
        return std::dynamic_pointer_cast <function_prototype> (found->second);
    } else {
        return std::shared_ptr <omni::core::function_prototype> ();
    }
}

/**
Removes the function `function' from this context. This only has an effect if `function' was previously added to this context by creating it using
createFunction or adding it via addFunction.
@param function The function to be removed from this context.
@return true, if `function' was part of this context and has been removed. false, if `function' was not found.
**/
bool omni::core::module::removeFunction (std::shared_ptr <omni::core::function_prototype> function)
{
    id_to_parts_map & functionMap (_parts [domain::function]);
    auto found = std::find_if (functionMap.begin (), functionMap.end (), [function] (std::pair <std::string, std::shared_ptr <context_part>> f) -> bool {
        return f.second == function;
    });
    if (found != functionMap.end ()) {
        found->second->setContext (nullptr);
        functionMap.erase (found);
        return true;
    } else {
        return false;
    }
}

/**
Sets the entry point for this context.
Not implemented yet.
TODO - this should be part of a module, not the whole context.
**/
void omni::core::module::setEntryPoint (std::shared_ptr <function> function)
{
    _entryPoint = function;
}

/**
Emits llvm IR language code to the file at path fileName.
@param fileName Path to the file where the code should be written to.
// TODO error reporting
**/
void omni::core::module::emitAssemblyFile (std::string const & fileName, const context_emit_options & options)
{
    std::string errorInfo;
    llvm::raw_fd_ostream fileStream (fileName.c_str (), errorInfo);
    emitAssemblyFile (fileStream, options);
}

/**
Emits llvm IR language code to the stream `stream'.
This function is not very fast since it first writes the whole code to a temporary buffer and then 
writes the whole buffer to `stream'. If you need a more efficient way, use emitAssemblyFile(llvm::raw_ostream).
@param stream The ostream where the code should be written to.
**/
void omni::core::module::emitAssemblyFile (std::ostream & stream, const context_emit_options & options)
{
    std::string tmp;
    llvm::raw_string_ostream rawStream (tmp);
    emitAssemblyFile (rawStream, options);
    stream << tmp;
}

/**
Emits llvm IR language code to the llvm stream `stream'.
@param stream The llvm stream wher the code should be written to.
**/
void omni::core::module::emitAssemblyFile (llvm::raw_ostream & stream, const context_emit_options & options)
{
    llvm::Module & m (llvmModule ());
    
    for (auto f : _parts [domain::function]) {
        function_prototype & func = * std::dynamic_pointer_cast <function_prototype> (f.second);
        func.llvmFunction ();
    }

    llvm::verifyModule (m, llvm::PrintMessageAction);

    llvm::PassManager pm;
    pm.add (llvm::createPrintModulePass (& stream));
    pm.run (m);
}

/**
Emits a native object file (e.g. .obj on win32) to stream.
This function is not very fast since it first writes the whole object file to a temporary buffer and then 
writes the whole buffer to `stream'. If you need a more efficient way, use emitObjectFile (llvm::raw_ostream).
@param stream Any ostream that should receive the content of the objectFile.
**/
void omni::core::module::emitObjectFile (std::ostream & stream, const context_emit_options & options)
{
    std::string tmp;
    llvm::raw_string_ostream rawStream (tmp);
    emitObjectFile (rawStream, options);
    stream << tmp;
}

/**
Emits a native object file (e.g. .obj on win32) to stream.
@param stream Any llvm::raw_ostream that should receive the content of the objectFile.
**/
void omni::core::module::emitObjectFile (llvm::raw_ostream & stream, const context_emit_options & options)
{
    llvm::Module & m (llvmModule ());
    
    addDllMainIfMissing (_context, m);
    
    for (auto f : _parts [domain::function]) {
        function_prototype & func = * std::dynamic_pointer_cast <function_prototype> (f.second);
        func.llvmFunction ();
    }

    std::string errorInfo;
    llvm::verifyModule (m, llvm::PrintMessageAction, & errorInfo);

    std::string errors;
    std::string targetTriple = "i686-pc-win32";
    llvm::Triple triple = llvm::Triple (targetTriple);
    llvm::InitializeAllTargets ();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmPrinters();
    llvm::InitializeAllAsmParsers();

    const llvm::Target * target = llvm::TargetRegistry::lookupTarget ("", triple, errors);
    llvm::TargetOptions targetOptions;
    llvm::TargetMachine * targetMachine = target->createTargetMachine (targetTriple, std::string (), std::string (), targetOptions);

    llvm::PassManager pm;
    llvm::formatted_raw_ostream formattedStream (stream);
    targetMachine->addPassesToEmitFile (pm, formattedStream, llvm::TargetMachine::CGFT_ObjectFile);
    pm.run (m);
    formattedStream.flush ();
}

/**
Emits a native object file (e.g. .obj on win32) to the file `fileName'.
@param fileName The path of the file where the object file should be written to.
**/
void omni::core::module::emitObjectFile (std::string const & fileName, const context_emit_options & options)
{
    std::string errorInfo;
    llvm::raw_fd_ostream rawStream (fileName.c_str (), errorInfo);
    emitObjectFile (rawStream, options);
}

/**
Emits a shared object file (.so on Linux/Unix, .dll on Windows or .dylib on Mac OS) to the file at the path `fileName'.
Remember to set functions to "external" with function::setExternal(true) when you want to export them from your shared object.
For every shared object file, an object file with the same base name but the extension .obj (on Windows) or .o (on Linux/Unix)
is temporarily created and removed before this function returns.
For example emitSharedLibraryFile /home/foo/shared.so will temporarily create a file /home/foo/shared.o.
**/
void omni::core::module::emitSharedLibraryFile (std::string const & fileName, const context_emit_options & options)
{
    boost::filesystem::path sharedLibraryPath (fileName);
    boost::filesystem::path objectFilePath = sharedLibraryPath;
    objectFilePath.replace_extension (".obj");
    emitObjectFile (objectFilePath.string (), options);
    /*
    boost::filesystem::path assemblyFilePath = objectFilePath;
    assemblyFilePath.replace_extension (".ll");
    emitAssemblyFile (assemblyFilePath.string ());
    */
    if (! boost::filesystem::exists (objectFilePath)) {
        throw omni::core::logic_error (__FILE__, __FUNCTION__, __LINE__, "Object file \"" + objectFilePath.string () + "\" does not exist");
    }
    std::set <std::string> additionalLibraries;
    additionalLibraries.insert ("LIBCMT.LIB");
    for (auto i : _parts) {
        for (auto p : i.second) {
            p.second->fillLibraries (additionalLibraries);
        }
    }
    std::string command = "..\\tools\\link_helper.cmd \"" + objectFilePath.string () + "\" \"/OUT:" + sharedLibraryPath.string () + "\"";
    for (auto librarySearchPath : options.getLibrarySearchPaths ()) {
        command += " /LIB:\"" + librarySearchPath.string () + "\"";
    }
    for (auto library : additionalLibraries) {
        command += " " + library;
    }
    int errorCode = std::system (command.c_str ());
    if (errorCode != 0) {
        throw std::runtime_error ((boost::format ("Linking the object file %1% failed.") % objectFilePath).str ().c_str ());
    }
    boost::system::error_code ignored;
    boost::filesystem::remove (objectFilePath, ignored); // ignores failures on purpose
//    boost::filesystem::remove (assemblyFilePath, errorCode); // ignores failures on purpose
}

llvm::Module & omni::core::module::llvmModule ()
{
    if (_llvmModule.get () == nullptr) {
        _llvmModule.reset (new llvm::Module (_name, _context.llvmContext ()));
    }
    return * _llvmModule;
}
