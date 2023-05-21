#ifndef LEXER_H   // Include guard to prevent multiple inclusion of the header file

#define LEXER_H   // Define a unique identifier for this header file



#include "llvm/ADT/StringRef.h"  // Include the necessary header files

#include "llvm/Support/MemoryBuffer.h"



class Lexer;   // Forward declare the Lexer class



class Token {   // Define a class for tokens

  friend class Lexer;   // Allow the Lexer class to access Token class's private members



public:

  enum TokenKind : unsigned short {   // Define an enumeration for different token kinds

    ID,            // Identefier

    NUM,           // Number

    LEFT_PAR,      // Left parentheses

    RIGHT_PAR,     // Right parentheses

    COMMA,         // Comma

    KW_TYPE,       // Keyword: type

    KW_INT,        // Keyword: int

    PLUS,          // Plus operator

    MINUS,         // Minus operator

    STAR,          // * operator

    SLASH,         // Slash operator

    EOI,           // End of input token

    EQUAL,         // Equals sign

    UNKNOWN,       // Unknown or invalid token

  };



private:

  TokenKind Kind;       // The kind of token (e.g. ID, NUM)

  llvm::StringRef Text; // The text of the token



public:

  TokenKind getKind() const { return Kind; }   // Getters for the token kind and text

  llvm::StringRef getText() const {

    return Text;

  }



  bool is(TokenKind K) const { return Kind == K; }   // Check if the token is of a certain kind

  bool isOneOf(TokenKind K1, TokenKind K2) const {    // Check if the token is either of two kinds

    return is(K1) || is(K2);

  }

  template <typename... Ts>

  bool isOneOf(TokenKind K1, TokenKind K2, Ts... Ks) const {   // Check if the token is any of a list of kinds

    return is(K1) || isOneOf(K2, Ks...);

  }

};



class Lexer {   // Define the Lexer class

  const char *BufferStart;   // Pointer to the start of the input buffer

  const char *BufferPtr;     // Pointer to the current position in the input buffer



public:

  Lexer(const llvm::StringRef &Buffer) {    // Constructor for the Lexer class that initializes BufferStart and BufferPtr

    BufferStart = Buffer.begin();

    BufferPtr = BufferStart;

  }



  void next(Token &token);   // Public function to get the next token from the input stream



private:

  void formToken(Token &Result, const char *TokEnd, Token::TokenKind Kind);   // Private helper function to update the Token object with the current token's details

};

#endif   // End of header file 

