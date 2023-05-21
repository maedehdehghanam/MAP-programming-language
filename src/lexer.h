#pragma once   // Preprocessor directive to include the header file only once at compile time

#include "llvm/ADT/StringRef.h"    // Include the necessary header files

enum TokenKind {    // Define an enumeration for different token kinds

    ID,        // Identefier

    NUM,       // Number

    LEFT_PAR,  // Left parentheses

    RIGHT_PAR, // Right parentheses

    COMMA,     // Comma

    KW_TYPE,   // Keyword: type

    KW_INT,    // Keyword: int

    PLUS,      // Plus operator

    MINUS,     // Minus operator

    STAR,      // * operator

    SLASH,     // Slash operator

    EQUAL,     // Equals sign

    SEMICOLON, // Semicolon

    EOI,       // End of input token

    UNKNOWN,   // Unknown or invalid token

};

class Token {   // Define a class for tokens
    private:
        TokenKind kind;             // The kind of token (e.g. ID, NUM)
        llvm::StringRef text;      // The text of the token

    public:
        Token(TokenKind kind, llvm::StringRef text) : kind {kind}, text {text} {}   // Constructor that initializes TokenKind and text

        TokenKind getKind() {      // Getter function for TokenKind and text

            return kind;

        } 

        llvm::StringRef getText() {

            return text;

        }
};

class Lexer {    // Define the Lexer class
    private:
        const char* bufferStart;   // Pointer to the start of the input buffer
        const char* bufferPtr;     // Pointer to the current position in the input buffer

    public:
        Lexer(llvm::StringRef &buffer) {    // Constructor that initializes bufferStart and bufferPtr

            bufferStart = buffer.begin();

            bufferPtr = bufferStart;

        }

        Token next();    // Public function to get the next token from the input stream

}; 

