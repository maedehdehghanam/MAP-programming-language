#ifndef SEMA_H
#define SEMA_H
#include#include"AST.h"
"Lexer.h"
class Sema {
	public:
	bool semantic(AST *Tree);
};
#endif