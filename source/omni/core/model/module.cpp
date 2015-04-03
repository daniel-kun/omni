#include <omni/core/model/module.hpp>
#include <omni/core/context.hpp>
#include <omni/core/model/function.hpp>
#include <omni/core/model/block.hpp>
#include <omni/core/logic_error.hpp>
#include <omni/core/already_exists_error.hpp>
#include <omni/core/verification_failed_error.hpp>

#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>

#include <boost/format.hpp>
#include <boost/filesystem.hpp>

#include <sstream>

// See meta_info.cpp for initialization.
namespace omniMetaImpl {
extern omni::core::model::meta_info moduleMetaInfo;
}

namespace {
    /**
    Adds a function with the prototype "dllexport x86_stdcallcc i8 @DllMain(i32*, i32, i32*)" if such a function does not already exist.
    TODO: Implement this in omni instead of llvm.
    **/
    void addDllMainIfMissing (omni::core::context & c, llvm::Module & module)
    {
#ifdef _MSC_VER
        llvm::Type * i32ptr = llvm::Type::getInt32PtrTy (c.llvmContext ());
        llvm::Type * i32 = llvm::Type::getInt32Ty (c.llvmContext ());
        llvm::Type * i8 = llvm::Type::getInt8Ty (c.llvmContext ());

        std::vector <llvm::Type *> params = { i32ptr, i32, i32ptr };
        llvm::FunctionType * ft = llvm::FunctionType::get (i8, params, false);
        llvm::Function * func = llvm::Function::Create (ft, llvm::Function::ExternalLinkage, "DllMain", & module);
        func->setDLLStorageClass (llvm::GlobalValue::DLLExportStorageClass);
        func->setCallingConv(llvm::CallingConv::X86_StdCall);
        llvm::BasicBlock * body = llvm::BasicBlock::Create (c.llvmContext (), "__entry__", func);
        llvm::IRBuilder <> builder (body);
        builder.CreateRet (llvm::ConstantInt::get (i8, 1));
#endif
    }
}

/**
Initializes this module in the context `context' with the name `name'. A new, random id will be assigned to this module.
**/
omni::core::model::module::module (omni::core::context & context, std::string name) :
    scope (name),
    _llvmModule (),
    _context (context),
    _entryPoint ()
{
}

/**
Initializes this existing module in the given context and the given name and moduleId.
**/
omni::core::model::module::module (context & context, id moduleId, std::string name) :
    scope (moduleId, name),
    _llvmModule (),
    _context (context),
    _entryPoint ()
{
}

omni::core::model::meta_info & omni::core::model::module::getStaticMetaInfo ()
{
    return omniMetaImpl::moduleMetaInfo;
}

omni::core::model::meta_info & omni::core::model::module::getMetaInfo () const
{
    return getStaticMetaInfo ();
}

omni::core::domain omni::core::model::module::getDomain () const
{
    return domain::module;
}

/**
Returns the context that this module is defined in.
**/
omni::core::context * omni::core::model::module::getContext ()
{
    return & _context;
}

/**
Returns the context that this module is defined in.
**/
const omni::core::context * omni::core::model::module::getContext () const
{
    return & _context;
}

omni::core::model::module * omni::core::model::module::getModule ()
{
    return this;
}

const omni::core::model::module * omni::core::model::module::getModule () const
{
    return this;
}

/**
Create a new, unique id for the domain `domain'.
@param domain The domain that the id should be valid for.
@return A new, unique id that can be used to identify newly created entities for this context.
**/
omni::core::id omni::core::model::module::createId (omni::core::domain domain)
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
    } while (lookupComponentById (id (domain, strId)).get () != nullptr);
    return id (domain, strId);
}

/**
Sets the entry point for this module.
Not implemented yet.
**/
void omni::core::model::module::setEntryPoint (std::shared_ptr <model::function> function)
{
    _entryPoint = function;
}

/**
Emits llvm IR language code to the file at path fileName.
@param fileName Path to the file where the code should be written to.
// TODO error reporting
**/
void omni::core::model::module::emitAssemblyFile (std::string const & fileName, const module_emit_options & options)
{
    std::error_code errorInfo;
    llvm::raw_fd_ostream fileStream (static_cast <llvm::StringRef> (fileName), errorInfo, llvm::sys::fs::F_None);
    emitAssemblyFile (fileStream, options);
}

/**
Emits llvm IR language code to the stream `stream'.
This function is not very fast since it first writes the whole code to a temporary buffer and then 
writes the whole buffer to `stream'. If you need a more efficient way, use emitAssemblyFile(llvm::raw_ostream).
@param stream The ostream where the code should be written to.
**/
void omni::core::model::module::emitAssemblyFile (std::ostream & stream, const module_emit_options & options)
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
void omni::core::model::module::emitAssemblyFile (llvm::raw_ostream & stream, const module_emit_options & options)
{
    llvm::Module & m (llvmModule ());
    
    for (auto f : getComponents (domain::function)) {
        model::function_prototype & func = * std::dynamic_pointer_cast <model::function_prototype> (f.second);
        func.llvmFunction ();
    }

    llvm::verifyModule(m, & llvm::outs ());

    llvm::legacy::PassManager pm;
    pm.add (llvm::createPrintModulePass (stream));
    pm.run (m);
}

/**
Emits a native object file (e.g. .obj on win32) to stream.
This function is not very fast since it first writes the whole object file to a temporary buffer and then 
writes the whole buffer to `stream'. If you need a more efficient way, use emitObjectFile (llvm::raw_ostream).
@param stream Any ostream that should receive the content of the objectFile.
**/
void omni::core::model::module::emitObjectFile (std::ostream & stream, const module_emit_options & options)
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
void omni::core::model::module::emitObjectFile (llvm::raw_ostream & stream, const module_emit_options & options)
{
    llvm::Module & m (llvmModule ());
    
    addDllMainIfMissing (_context, m);
    
    for (auto f : getComponents (domain::function)) {
        model::function_prototype & func = * std::dynamic_pointer_cast <model::function_prototype> (f.second);
        func.llvmFunction ();
    }

    std::string errorInfo;
    llvm::raw_string_ostream errorStream (errorInfo);
    if (llvm::verifyModule(m, & errorStream)) {
        errorStream.flush ();
        throw verification_failed_error (getName (), errorInfo);
    }

    std::string errors;
#ifdef WIN32
    std::string targetTriple = "i686-pc-win32";
#else
#   ifdef OMNI_ARM
    std::string targetTriple = "armv6-unknown-linux-gnueabi";
#   else
    std::string targetTriple = "x86_64-pc-linux";
#   endif
#endif
    llvm::Triple triple = llvm::Triple (targetTriple);

    llvm::InitializeNativeTarget ();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();

    const llvm::Target * target = llvm::TargetRegistry::lookupTarget ("", triple, errors);
    llvm::TargetOptions targetOptions;
#ifdef OMNI_ARM
    // Required to output Hard-Float object code. Otherwise linking will fail with error message "*.so uses VFP register arguments, *.o does not".
    targetOptions.FloatABIType = llvm::FloatABI::Hard;
#endif
    llvm::TargetMachine * targetMachine = target->createTargetMachine (targetTriple, std::string (), std::string (), targetOptions, llvm::Reloc::PIC_);

    llvm::legacy::PassManager pm;
    llvm::formatted_raw_ostream formattedStream (stream);
    targetMachine->addPassesToEmitFile (pm, formattedStream, llvm::TargetMachine::CGFT_ObjectFile);
    pm.run (m);
    formattedStream.flush ();
}

/**
Emits a native object file (e.g. .obj on win32) to the file `fileName'.
@param fileName The path of the file where the object file should be written to.
**/
void omni::core::model::module::emitObjectFile (std::string const & fileName, const module_emit_options & options)
{
    std::error_code errorInfo;
    llvm::raw_fd_ostream rawStream (static_cast <llvm::StringRef> (fileName), errorInfo, llvm::sys::fs::F_None);
    emitObjectFile (rawStream, options);
}

/**
Emits a shared object file (.so on Linux/Unix, .dll on Windows or .dylib on Mac OS) to the file at the path `fileName'.
Remember to set functions to "external" with function::setExternal(true) when you want to export them from your shared object.
For every shared object file, an object file with the same base name but the extension .obj (on Windows) or .o (on Linux/Unix)
is temporarily created and removed before this function returns.
For example emitSharedLibraryFile /home/foo/shared.so will temporarily create a file /home/foo/shared.o.
**/
void omni::core::model::module::emitSharedLibraryFile (std::string const & fileName, const module_emit_options & options)
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
    for (auto i : getComponents ()) {
        for (auto p : i.second) {
            p.second->fillLibraries (additionalLibraries);
        }
    }
#ifdef WIN32
    additionalLibraries.insert ("LIBCMT.LIB");
    std::string command = "..\\tools\\link_helper.cmd \"" + objectFilePath.string () + "\" \"/OUT:" + sharedLibraryPath.string () + "\"";
    // Add library search path:
    for (auto librarySearchPath : options.getLibrarySearchPaths ()) {
        command += " /LIBPATH:\"" + librarySearchPath.string () + "\"";
    }
    std::string linkLibraryPrefix = " ";
#else
#   ifdef OMNI_ARM
    std::string ldFlags = "-mfloat-abi=hard -mfpu=vfpu";
#   else
    std::string ldFlags;
#   endif
    std::string command = "gcc -shared \"" + objectFilePath.string () + "\" " + ldFlags + " -o \"" + sharedLibraryPath.string () + "\"";
    // Add library search paths:
    for (auto librarySearchPath : options.getLibrarySearchPaths ()) {
        command += " -L\"" + librarySearchPath.string () + "\"";
    }
    std::string linkLibraryPrefix = " -l";
#endif
    // Add libraries to link:
    for (auto library : additionalLibraries) {
        if (library.length () > 0) {
            command += linkLibraryPrefix + library;
        }
    }
    for (auto library : options.getLibraries ()) {
        if (library.length () > 0) {
            command += linkLibraryPrefix + library;
        }
    }

    // Now call the linker:
    int errorCode = std::system (command.c_str ());

    if (errorCode != 0) {
        throw std::runtime_error ((boost::format ("Linking the object file %1% failed with command %2%.") % objectFilePath % command).str ().c_str ());
    }
    boost::system::error_code ignored;
    boost::filesystem::remove (objectFilePath, ignored); // ignores failures on purpose
}

/**
Verifies this module.
@param errorInfo When the module contains errors, errorInfo will be filled with the error messages.
@return True, if the module is valid. false, if there are errors.
**/
bool omni::core::model::module::verify (std::string & errorInfo)
{
    llvm::Module & m (llvmModule ());

    try {
        for (auto f : getComponents (domain::function)) {
            model::function_prototype & func = *std::dynamic_pointer_cast <model::function_prototype> (f.second);
            func.llvmFunction ();
        }
    }
    catch (std::exception const & e) {
        errorInfo = e.what ();
        return false;
    }

    return !llvm::verifyModule(m, & llvm::outs ());
}

/**
@internal
**/
llvm::Module & omni::core::model::module::llvmModule ()
{
    if (_llvmModule.get () == nullptr) {
        _llvmModule.reset (new llvm::Module (getName (), _context.llvmContext ()));
    }
    return * _llvmModule;
}
