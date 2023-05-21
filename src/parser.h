#pragma once

#include "AST.h"
#include "lexer.h"
#include "llvm/Support/raw_ostream.h"

class Parser {
  Lexer &Lex;
  Token Tok;
  bool HasError;

  void error() {
    llvm::errs() << "Unexpected: " << Tok.getText() << "\n";
    HasError = true;
  }

  void advance() { Tok = Lex.next(); }

  bool expect(TokenKind Kind) {
    if (Tok.getKind() != Kind) {
      error();
      return true;
    }
    return false;
  }

  bool consume(TokenKind Kind) {
    if (expect(Kind))
      return true;
    advance();
    return false;
  }

  AST *parseGoal();
  Statement *parseStatement();
  VarDecl *parseVarDecl();
  Assignment *parseAssignment();
  Expr *parseExpr();
  Expr *parseTerm();
  Expr *parseFactor();

public:
  Parser(Lexer &Lex) : Tok(UNKNOWN, ""), Lex(Lex), HasError(false) {
    advance();
  }
  AST *parse();
  bool hasError() { return HasError; }
};