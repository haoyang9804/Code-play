#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Basic/SourceLocation.h"
#include "clang/Basic/FileEntry.h"
#include "FileReader.hpp"
#include "clang/Rewrite/Core/Rewriter.h"


using namespace clang;

class FindNamedClassVisitor
  : public RecursiveASTVisitor<FindNamedClassVisitor> {
public:
  explicit FindNamedClassVisitor(Rewriter& rewriter, ASTContext *Context, SourceManager& SM)
    : rewriter(rewriter), Context(Context), SM(SM) {}

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

      // SourceRange funcRange = Declaration->getSourceRange();

      // IdentifierInfo* barId = &Context->Idents.get("bar");
      // DeclarationName barName(barId);
      // Declaration->setDeclName(barName);
      DeclarationNameInfo nameinfo = Declaration->getNameInfo();
      SourceLocation nameloc = nameinfo.getLoc();
      llvm::errs() << "func foo name loc is " << nameloc.printToString(SM) << "\n";
      SourceRange funcRange = Declaration->getSourceRange();
      SourceLocation locBegin = funcRange.getBegin();
      SourceLocation locEnd = funcRange.getEnd();
      llvm::errs() << "func foo loc begin at " << locBegin.printToString(SM) << "\n";
      llvm::errs() << "func foo loc end at " << locEnd.printToString(SM) << "\n";
      llvm::errs() << "func name length is " << Declaration->getQualifiedNameAsString().size() << "\n";
      bool rewrite_result = rewriter.ReplaceText(nameloc, Declaration->getQualifiedNameAsString().size(), llvm::StringRef("barr"));
      // Don't know why... returning true means fail but returning false means succeeds
      llvm::errs() << "Rewriting foo into bar " << (rewrite_result ? "fails" : "succeeds") << "\n";
    }
    return true;
  }

private:
  ASTContext *Context;
  Rewriter &rewriter;
  SourceManager &SM;
};

class FindNamedClassConsumer : public clang::ASTConsumer {
public:
  explicit FindNamedClassConsumer(Rewriter& rewriter, ASTContext *Context, SourceManager& SM)
    : Visitor(rewriter, Context, SM) {}

  virtual void HandleTranslationUnit(clang::ASTContext &Context) {
    Visitor.TraverseDecl(Context.getTranslationUnitDecl());
  }
private:
  FindNamedClassVisitor Visitor;
};

class FindNamedClassAction : public clang::ASTFrontendAction {
public:
  std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
    clang::CompilerInstance &Compiler, llvm::StringRef InFile) override {
    
    rewriter.setSourceMgr(Compiler.getSourceManager(), Compiler.getLangOpts());

    return std::unique_ptr<clang::ASTConsumer>(
        new FindNamedClassConsumer(rewriter, &Compiler.getASTContext(), Compiler.getSourceManager()));
  }

  void EndSourceFileAction() override {
    llvm::errs() << "Here goes EndSourceFileAction\n";
    bool rewriterChangeFileResult = rewriter.overwriteChangedFiles();
    // Don't know why... returning true means fail but returning false means succeeds
    // And don't know why again. Clang will create a new file named ``input.cc'' in build folder
    llvm::errs() << "overwriteChangedFiles " << (rewriterChangeFileResult ? "fails" : "succeeds") << "\n";
  }
private:
  Rewriter rewriter;
};

int main(int argc, char **argv) {
  if (argc > 1) {
    std::unique_ptr<FindNamedClassAction> fnca_ptr = std::make_unique<FindNamedClassAction>();
    clang::tooling::runToolOnCode(std::move(fnca_ptr), readFile(argv[1]));
  }
}