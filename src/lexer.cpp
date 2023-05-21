#include "./lexer.h"

class Lexer {
    private:
        const char* bufferStart;
        const char* bufferPtr;

    public:
        Token next() {
            return Token(EOI, "");
        }
};