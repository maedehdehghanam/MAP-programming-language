#pragma once

#include "llvm/ADT/StringRef.h"

enum TokenKind {
    ID,
    NUM,
    LEFT_PAR,
    RIGHT_PAR,
    COMMA,
    KW_TYPE,
    KW_INT,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    EOI,
    UNKNOWN,
};

class Token {
    private:
        TokenKind kind;
        llvm::StringRef text;
    
    public:
        Token(TokenKind kind, llvm::StringRef text) : kind {kind}, text {text} {}


        TokenKind getKind() {
            return kind;
        } 

        llvm::StringRef getText() {
            return text;
        }
};

class Lexer {
    private:
        const char* bufferStart;
        const char* bufferPtr;

    public:
        Lexer(llvm::StringRef &buffer) {
            bufferStart = buffer.begin();
            bufferPtr = bufferStart;
        }

        Token next();
};