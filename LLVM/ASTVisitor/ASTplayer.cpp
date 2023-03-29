#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"
#include "FileReader.hpp"
#include "clang/Rewrite/Core/Rewriter.h"


using namespace clang;

class FindNamedClassVisitor
  : public RecursiveASTVisitor<FindNamedClassVisitor> {
public:
  explicit FindNamedClassVisitor(ASTContext *Context)
    : Context(Context) {}

  bool VisitCXXRecordDecl(CXXRecordDecl *Declaration) {
    if (Declaration->getQualifiedNameAsString() == "n::m::C") {
      FullSourceLoc FullLocation = Context->getFullLoc(Declaration->getBeginLoc());
      if (FullLocation.isValid())
        llvm::outs() << "CXXRecordDecl: Found declaration at "
                     << FullLocation.getSpellingLineNumber() << ":"
                     << FullLocation.getSpellingColumnNumber() << ", "
                     << FullLocation.getExpansionLineNumber() << ":"
                     << FullLocation.getExpansionColumnNumber() << "\n";
    }
    return true;
  }

  bool VisitRecordDecl(RecordDecl *Declaration) {
    if (Declaration->getQualifiedNameAsString() == "n::m::C") {
      FullSourceLoc FullLocation = Context->getFullLoc(Declaration->getBeginLoc());
      if (FullLocation.isValid())
        llvm::outs() << "RecordDecl: Found declaration at "
                     << FullLocation.getSpellingLineNumber() << ":"
                     << FullLocation.getSpellingColumnNumber() << ", "
                     << FullLocation.getExpansionLineNumber() << ":"
                     << FullLocation.getExpansionColumnNumber() << "\n";
    }
    return true;
  }

  bool VisitTagDecl(TagDecl *Declaration) {
    if (Declaration->getQualifiedNameAsString() == "n::m::C") {
      FullSourceLoc FullLocation = Context->getFullLoc(Declaration->getBeginLoc());
      if (FullLocation.isValid())
        llvm::outs() << "TagDecl: Found declaration at "
                     << FullLocation.getSpellingLineNumber() << ":"
                     << FullLocation.getSpellingColumnNumber() << ", "
                     << FullLocation.getExpansionLineNumber() << ":"
                     << FullLocation.getExpansionColumnNumber() << "\n";
    }
    return true;
  }

  bool VisitFunctionDecl(FunctionDecl *Declaration) {
    if (Declaration->getQualifiedNameAsString() == "foo") {
      IdentifierInfo* barId = &Context->Idents.get("bar");
      DeclarationName barName(barId);
      Declaration->setDeclName(barName);
      // Rewriter rewriter(Context->getSourceManager(), astUnit->getLangOpts());
    }
    return true;
  }

private:
  ASTContext *Context;
};

class FindNamedClassConsumer : public clang::ASTConsumer {
public:
  explicit FindNamedClassConsumer(ASTContext *Context)
    : Visitor(Context) {}

  virtual void HandleTranslationUnit(clang::ASTContext &Context) {
    Visitor.TraverseDecl(Context.getTranslationUnitDecl());
  }
private:
  FindNamedClassVisitor Visitor;
};

class FindNamedClassAction : public clang::ASTFrontendAction {
public:
  virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
    clang::CompilerInstance &Compiler, llvm::StringRef InFile) {
    return std::unique_ptr<clang::ASTConsumer>(
        new FindNamedClassConsumer(&Compiler.getASTContext()));
  }
};

int main(int argc, char **argv) {
  if (argc > 1) {
    std::unique_ptr<FindNamedClassAction> fnca_ptr = std::make_unique<FindNamedClassAction>();
    clang::tooling::runToolOnCode(std::move(fnca_ptr), readFile(argv[1]));
  }
}