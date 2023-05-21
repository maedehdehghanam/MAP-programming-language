#ifndef AST_H
#define AST_H

#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"
#include <string>

class AST;
class Statemanet;
class VarDec;
class Assigment;
class Expr;
class Factor;
class BinaryOp;
class TypeDecl;

class ASTVisitor {
public:
  virtual void visit(AST &){} = 0;
  virtual void visit(Expr &){} = 0;
  virtual void visit(Factor &) = 0;
  virtual void visit(Statement &) = 0;
  virtual void visit(Assigment &) =0;
  virtual void visit(VarDec &) =0;

  virtual void visit(BinaryOp &) = 0;
  virtual void visit(WithDecl &) = 0;
};

class AST {
public:
  virtual ~AST() {}
  virtual void accept(ASTVisitor &V) = 0;
};

class Statement : public AST {
public:
  Statement() {

  }
};
class VarDecl : public Statement{
    using VarVector = llvm::SmallVector<llvm::StringRef, 8>;
    VarVector vector;
  public:
    VarDecl(llvm::SmallVector<llvm::StringRef, 8> Vars): Vars(Vars) {}
    VarVector::const_iterator begin() { return Vars.begin(); }
    VarVector::const_iterator end() { return Vars.end(); }
    virtual void accept(ASTVisitor &V) override {
      V.visit(*this);
    }



};

class Assigment : public Statement{
  Expr *E;
  string id;

  public:
    Assigment(Expr *E,sting id): E(E), id(id) {}
    Expr get_Expr()
    {
      return Expr;
    }
    string get_id()
    {
      return id;
    }
};

class Expr : public Assigment{

  public:
    Expr() {}
};

class Factor : public Expr {
public:
  enum ValueKind { Ident, Number };

private:
  ValueKind Kind;
  llvm::StringRef Val;

public:
  Factor(ValueKind Kind, llvm::StringRef Val)
      : Kind(Kind), Val(Val) {}
  ValueKind getKind() { return Kind; }
  llvm::StringRef getVal() { return Val; }
  virtual void accept(ASTVisitor &V) override {
    V.visit(*this);
  }
};

class BinaryOp : public Expr {
public:
  enum Operator { Plus, Minus, Mul, Div };

private:
  Expr *Left;
  Expr *Right;
  Operator Op;

public:
  BinaryOp(Operator Op, Expr *L, Expr *R)
      : Op(Op), Left(L), Right(R) {}
  Expr *getLeft() { return Left; }
  Expr *getRight() { return Right; }
  Operator getOperator() { return Op; }
  virtual void accept(ASTVisitor &V) override {
    V.visit(*this);
  }
};

#endif
