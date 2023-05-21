#include "Parser.h"

AST *Parser::parse() {
  AST *Res = parseCalc();
  expect(Token::eoi);
  return Res;
}
VarDecl *Parser::parseVarDeclr()
{
    advance();
    if (expect(Token::KW_INT))
      goto _error;
    Vars.push_back(Tok.getText());
    advance();
    while (Tok.is(Token::COMMA)) {
      advance();
      if (expect(Token::ident))
        goto _error;
      Vars.push_back(Tok.getText());
      advance();
    _error:
      return nullptr;
}
Statemanet *Parser::parseStatement()
{
    if (Tok.is(Token::KW_TYPE)) {
      VarDecler vardecler=parseVarDeclr();
      if (vardecler == nullptr)
      {
        goto _error;
      }

    }
  }
  if (Tok.is(Token::ID))
  {
    advance();
    if (expect(Token::EQUAL))
      goto _error;
    
  }
  E = parseExpr();
  if (Vars.empty())
    return E;
  else
    return new WithDecl(Vars, E);

  _error:
    return nullptr;
}
AST *Parser::parseGoal() {
  Expr *E;
  llvm::SmallVector<llvm::StringRef, 8> Vars;
  while (1)
  {
    Statement statemnt = parseStatment();
    if (statemnt == nullptr)
    {
      goto _error;
    }
    if ((expect(Token::SEMICOLUMN)))
    {
      goto _error;
    }
    if ((!expect(Token::EOI)))
    {
      break;
    }
    
  }
  

_error:
  while (Tok.getKind() != Token::eoi)
    advance();
  return nullptr;
}

Expr *Parser::parseExpr() {
  Expr *Left = parseTerm();
  while (Tok.isOneOf(Token::plus, Token::minus)) {
    BinaryOp::Operator Op = Tok.is(Token::plus)
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
  while (Tok.isOneOf(Token::star, Token::slash)) {
    BinaryOp::Operator Op =
        Tok.is(Token::star) ? BinaryOp::Mul : BinaryOp::Div;
    advance();
    Expr *Right = parseFactor();
    Left = new BinaryOp(Op, Left, Right);
  }
  return Left;
}

Expr *Parser::parseFactor() {
  Expr *Res = nullptr;
  switch (Tok.getKind()) {
  case Token::number:
    Res = new Factor(Factor::Number, Tok.getText());
    advance(); break;
  case Token::ident:
    Res = new Factor(Factor::Ident, Tok.getText());
    advance(); break;
  case Token::l_paren:
    advance();
    Res = parseExpr();
    if (!consume(Token::r_paren)) break;
  default:
    if (!Res)
      error();
    while (!Tok.isOneOf(Token::r_paren, Token::star,
                        Token::plus, Token::minus,
                        Token::slash, Token::eoi))
      advance();
  }
  return Res;
}
