#include "./lexer.h"

bool isWhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\f' || c == '\v' ||
         c == '\r' || c == '\n';
}

bool isNumeric(char c) {
    return c >= '0' && c <= '9';
}

bool isLetter(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

Token Lexer::next() {
    while(*bufferPtr && isWhitespace(*bufferPtr)) bufferPtr++;

    if (!*bufferPtr) return Token(EOI, "");

    if (isLetter(*bufferPtr)) {
        const char* end = bufferPtr + 1;
        while(isLetter(*end)) end++;

        llvm::StringRef curTokenText(bufferPtr, end - bufferPtr);

        bufferPtr = end;

        if (curTokenText == "type") return Token(KW_TYPE, "");
        if (curTokenText == "int") return Token(KW_INT, "");
        else return Token(ID, curTokenText);
    } else if (isNumeric(*bufferPtr)) {
        const char* end = bufferPtr + 1;
        while(isNumeric(*end)) end++;

        llvm::StringRef numberLiteral(bufferPtr, end - bufferPtr);
        
        bufferPtr = end;

        return Token(NUM, numberLiteral);
    }

    Token result(UNKNOWN, "");

    switch (*bufferPtr) {
        case '+': {
            result = Token(PLUS, "");
            break;
        }
        case '-': {
            result = Token(STAR, "");
            break;
        }
        case '*': {
            result = Token(STAR, "");
            break;
        } case '/': {
            result = Token(SLASH, "");
            break;
        } case '(': {
            result = Token(LEFT_PAR, "");
            break;
        } case ')': {
            result = Token(RIGHT_PAR, "");
            break;
        } case ';': {
            result = Token(SEMICOLON, "");
            break;
        } case '=': {
            result = Token(EQUAL, "");
            break;
        } case ',': {
            result = Token(COMMA, "");
            break;
        } default :
    }

    bufferPtr++;
    return result;
}