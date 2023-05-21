#include "parser.h"

AST *Parser::parse() {
  AST *Res = parseGoal();
  expect(EOI);
  return Res;
}

AST *Parser::parseGoal() {
  std::vector<Statement*> statements;

  while (Tok.getKind() != EOI) {
    Statement* curStat = parseStatement();
    if (curStat == nullptr) goto _error;
    else statements.push_back(curStat);
  }

  return new Goal(statements);

  _error:
  while (Tok.getKind() != EOI) advance();
    return nullptr;
}

Statement *Parser::parseStatement() {
  if (Tok.getKind() == KW_TYPE) {
    return parseVarDecl();
  } else if (Tok.getKind() == ID) {
    return parseAssignment();
  } else {
    while (Tok.getKind() != EOI) advance();
    return nullptr;
  }
}

VarDecl *Parser::parseVarDecl() {

  VarDecl::VarVector vars;

  if (expect(KW_TYPE)) {
    goto _error;
  }
  advance();
  if (expect(KW_INT)) {
    goto _error;
  }
  advance();
  if (expect(ID)) {
    goto _error;
  }
  vars.push_back(Tok.getText());
  advance();

  while (Tok.getKind() == COMMA) {
    advance();
    if (expect(ID)) goto _error;
    vars.push_back(Tok.getText());
    advance();
  }

  if (expect(SEMICOLON)) goto _error;
  
  return new VarDecl(vars);

  _error:
  while (Tok.getKind() != EOI) advance();
    return nullptr;
}

Assignment* Parser::parseAssignment() {
  std::string id;
  Expr *rhs = nullptr;

  if (expect(ID)) goto _error;
  advance();
  if (expect(EQUAL)) goto _error;
  advance();

  rhs = parseExpr();

  return new Assignment(rhs, id);

  _error:
  while (Tok.getKind() != EOI) advance();
    return nullptr;
}

Expr *Parser::parseExpr() {
  Expr *Left = parseTerm();
  while (Tok.getKind() == PLUS || Tok.getKind() == MINUS) {
    BinaryOp::Operator Op = Tok.getKind() == PLUS
                                ? BinaryOp::Plus
                                : BinaryOp::Minus;
    advance();
    Expr *Right = parseTerm();
    Left = new BinaryOp(Op, Left, Right);
  }
  return Left;
}

Expr *Parser::parseTerm() {
  Expr *Left = parseFactor();
  while (Tok.getKind() == STAR || Tok.getKind() == SLASH) {
    BinaryOp::Operator Op =
        Tok.getKind() == STAR ? BinaryOp::Mul : BinaryOp::Div;
    advance();
    Expr *Right = parseFactor();
    Left = new BinaryOp(Op, Left, Right);
  }
  return Left;
}

Expr *Parser::parseFactor() {
  Expr *Res = nullptr;
  switch (Tok.getKind()) {
  case NUM:
    Res = new Factor(Factor::Number, Tok.getText());
    advance(); break;
  case ID:
    Res = new Factor(Factor::Ident, Tok.getText());
    advance(); break;
  case LEFT_PAR:
    advance();
    Res = parseExpr();
    if (!consume(RIGHT_PAR)) break;
  default:
    if (!Res)
      error();
    while (!(Tok.getKind() == RIGHT_PAR || Tok.getKind() == STAR,
                        Tok.getKind() == PLUS || Tok.getKind() == MINUS ||
                        Tok.getKind() == SLASH || Tok.getKind() == EOI))
      advance();
  }
  return Res;
}
