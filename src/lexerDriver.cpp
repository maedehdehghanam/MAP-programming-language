#include <iostream>
#include <string>

#include "lexer.h"
#include "llvm/ADT/StringRef.h"

std::string tokenKindToString(const TokenKind& tk) {
    switch (tk) {
        case ID: return "ID";
        case NUM: return "NUM";
        case LEFT_PAR: return "LEFT_PAR";
        case RIGHT_PAR: return "RIGHT_PAR";
        case COMMA: return "COMMA";
        case KW_TYPE: return "KW_TYPE";
        case KW_INT: return "KW_INT";
        case PLUS: return "PLUS";
        case MINUS: return "MINUS";
        case STAR: return "STAR";
        case SLASH: return "SLASH";
        case EQUAL: return "EQUAL";
        case SEMICOLON: return "SEMICOLON";
        case EOI: return "EOI";
        case UNKNOWN: return "UNKNOWN";
    }

    return "";
}

void printToken(Token& t) {
    std::cout << tokenKindToString(t.getKind()) << ' ' << t.getText().str() << std::endl;
}

int main() {

    std::string input;
    std::getline(std::cin, input);

    llvm::StringRef inputStringRef(input);

    Lexer inputLexer(inputStringRef);

    Token curToken = inputLexer.next();

    while (curToken.getKind() != TokenKind::EOI) {
        printToken(curToken);
        curToken = inputLexer.next();
    }

    printToken(curToken);



    return 0;

}