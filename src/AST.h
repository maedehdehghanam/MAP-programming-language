#ifndef AST_H
#define AST_H

#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"
#include <string>

class AST;
class Statement;
class VarDecl;
class Assignment;
class Expr;
class Factor;
class BinaryOp;
class TypeDecl;

class ASTVisitor {
public:
  virtual void visit(AST &) = 0;
  virtual void visit(Expr &) = 0;
  virtual void visit(Factor &) = 0;
  virtual void visit(Statement &) = 0;
  virtual void visit(Assignment &) =0;
  virtual void visit(VarDecl &) =0;

  virtual void visit(BinaryOp &) = 0;
  // virtual void visit(VarDecl &) = 0;
};

class AST {
public:
  virtual ~AST() {}
  virtual void accept(ASTVisitor &V) = 0;
};

class Goal : public AST{
  std::vector<Statement*> statements;

  public:

    Goal(std::vector<Statement*> statements) : statements{statements} {}

    virtual void accept(ASTVisitor &V) override {
        V.visit(*this);
    }
};

class Statement : public AST {

};

class VarDecl : public Statement {
    public:
      using VarVector = llvm::SmallVector<llvm::StringRef, 8>;
    
    private:
      VarVector vector;

  public:
    VarDecl(llvm::SmallVector<llvm::StringRef, 8> Vars): vector(Vars) {}
    VarVector::const_iterator begin() { return vector.begin(); }
    VarVector::const_iterator end() { return vector.end(); }
    virtual void accept(ASTVisitor &V) override {
      V.visit(*this);
    }
};

class Assignment : public Statement{
  Expr *E;
  std::string id;

  public:
    Assignment(Expr *E, std::string id): E(E), id(id) {}
    
    Expr* getExpr() {
      return E;
    }

    std::string getId() {
      return id;
    }

    virtual void accept(ASTVisitor &V) override {
      V.visit(*this);
    }
};

class Expr : public AST {

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
