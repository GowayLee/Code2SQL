#ifndef _AST_ANALYZER_H_
#define _AST_ANALYZER_H_

#pragma once
#include "ast_node_info.h"
#include <clang-c/Index.h>
#include <string>
#include <vector>

namespace ast {
class ASTAnalyzer {
public:
  ASTAnalyzer();
  ~ASTAnalyzer();

  bool parseFile(const std::string &filename);

  // Analyzer functions
  const std::vector<FunctionDecl> &getFunctions() const;
  const std::vector<CallExpr> &getCalls() const;
  const std::vector<VarDecl> &getVariables() const;
  const std::vector<DeclRefExpr> &getReferences() const;

private:
  // Storage for parsed AST nodes
  std::vector<FunctionDecl> functions;
  std::vector<CallExpr> calls;
  std::vector<VarDecl> variables;
  std::vector<DeclRefExpr> references;

  CXIndex index;
  CXTranslationUnit unit;

  // 访问者模式Call back function
  static CXChildVisitResult visitNode(CXCursor cursor, CXCursor parent,
                                      CXClientData clientData);

  void handleFunctionDecl(CXCursor cursor);
  void handleCallExpr(CXCursor cursor);
  void handleVarDecl(CXCursor cursor);
  void handleDeclRefExpr(CXCursor cursor);
};

} // namespace ast

#endif
