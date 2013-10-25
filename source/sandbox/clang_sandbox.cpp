#include "clang_sandbox.hpp"
#include <clang/Frontend/ASTConsumers.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/CodeGen/CodeGenAction.h>
#include <clang/Tooling/Tooling.h>
#include <clang/Sema/Sema.h>
#include <clang/Lex/Preprocessor.h>
#include <clang/AST/Decl.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/DeclarationName.h>
#include <clang/Basic/FileManager.h>
#include <clang/Basic/TargetInfo.h>
#include <clang/Basic/IdentifierTable.h>
#include <clang/Basic/SourceLocation.h>
#include <llvm/Support/raw_os_ostream.h>
#include <llvm/Support/Host.h>
#include <llvm/ADT/ArrayRef.h>
#include <iostream>
#include <string>

void clang_sandbox ()
{
    clang::FileManager fileManager = clang::FileManager (clang::FileSystemOptions ());
    auto targetOptions = new clang::TargetOptions ();
    targetOptions->Triple = llvm::sys::getDefaultTargetTriple ();

    clang::CompilerInstance instance;
    instance.createDiagnostics ();
    instance.createFileManager ();
    instance.createSourceManager (fileManager);
    clang::TargetInfo * target (clang::TargetInfo::CreateTargetInfo (instance.getDiagnostics (), targetOptions));
    // This setTarget is necessary for createPreprocessor.
    // However, another setTarget is made in instance.ExecuteAction later, which uses the targetOpts. Hence we have to set the targetOpts, too.
    instance.setTarget (target); 
    instance.getTargetOpts () = * targetOptions;
    instance.createPreprocessor ();
    instance.setASTConsumer (clang::CreateASTPrinter (nullptr, llvm::StringRef ()));
    instance.createASTContext ();

    auto sema = new clang::Sema (instance.getPreprocessor (), instance.getASTContext (), instance.getASTConsumer (), clang::TU_Complete);

    clang::IdentifierTable & identifierTable = sema->getPreprocessor ().getIdentifierTable ();
    clang::IdentifierInfo & nsIdentifier = identifierTable.get ("blubb");
    clang::IdentifierInfo & fnIdentifier = identifierTable.get ("foo");

    clang::TranslationUnitDecl* tu = instance.getASTContext().getTranslationUnitDecl();
    clang::DeclContext* declContext = tu->getPrimaryContext();

    clang::SourceLocation defaultSourceLocation;

    clang::NamespaceDecl * nameSpace = clang::NamespaceDecl::Create (
        instance.getASTContext (), // ASTContext &C
        declContext,            // DeclContext *DC
        false,                  // bool Inline
        defaultSourceLocation,  // SourceLocation StartLoc
        defaultSourceLocation,  // SourceLocation IdLoc
        & nsIdentifier,         // IdentifierInfo *Id
        nullptr);               // NamespaceDecl *PrevDecl


    clang::DeclarationNameInfo fnDeclNameInfo = clang::DeclarationNameInfo (clang::DeclarationName (& fnIdentifier), defaultSourceLocation);
    clang::QualType qualType;

    clang::FunctionDecl * functionDecl = clang::FunctionDecl::Create (
        instance.getASTContext (),
        nameSpace,
        defaultSourceLocation,
        defaultSourceLocation,
        clang::DeclarationName (& fnIdentifier),
        qualType,
        nullptr,
        clang::SC_None);

    llvm::ArrayRef <clang::Stmt *> emptyStatementArray;
    clang::CompoundStmt functionBody = clang::CompoundStmt (
        instance.getASTContext (),
        emptyStatementArray,
        defaultSourceLocation,
        defaultSourceLocation);
    functionDecl->setBody (& functionBody);

    instance.setSema (sema);
    clang::ASTDumpAction action;
    instance.ExecuteAction (action);

    std::cout << "\nEnd CLang Sandbox!\n";
}

void clang_sandbox_compiler ()
{
    clang::FrontendInputFile inputFile ("D:/temp/blubb.cpp", clang::IK_CXX);
    clang::FileManager fileManager = clang::FileManager (clang::FileSystemOptions ());

    clang::CompilerInstance instance;
    instance.createDiagnostics ();
    auto targetOptions = new clang::TargetOptions ();
    targetOptions->Triple = "i386-pc-win32";
    std::shared_ptr <clang::TargetInfo> target (clang::TargetInfo::CreateTargetInfo (instance.getDiagnostics (), targetOptions));
    instance.setTarget (target.get ());
    instance.createFileManager ();
    instance.createSourceManager (fileManager);
    instance.createPreprocessor ();
//    instance.createASTContext ();

    clang::ASTDumpAction action;
    action.setCompilerInstance (& instance);
    action.setCurrentInput (inputFile);
    action.Execute ();

    //clang::tooling::runToolOnCode (& action, "int foo () { return 10; }");
    std::cout << "\nEnd CLang Sandbox!\n";
}
