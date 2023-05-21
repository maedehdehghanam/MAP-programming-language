#include "./lexer.h" 

// Function to check for whitespace characters
bool isWhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\f' || c == '\v' || c == '\r' || c == '\n';
}

// Function to check if a character is numeric 
bool isNumeric(char c) {
    return c >= '0' && c <= '9';
}

// Function to check if a character is a letter
bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// Function to get the next token from the input stream
Token Lexer::next() {

    // Skip over any whitespace characters
    while(*bufferPtr && isWhitespace(*bufferPtr)) bufferPtr++;

    // If we've reached the end of the buffer, return an EOI token
    if (!*bufferPtr) return Token(EOI, "");

    // If the current character is a letter, it's either a keyword or an identifier
    if (isLetter(*bufferPtr)) {
        const char* end = bufferPtr + 1;
        while(isLetter(*end)) end++;

        // Get the text of the current token
        llvm::StringRef curTokenText(bufferPtr, end - bufferPtr);

        // Update the buffer pointer
        bufferPtr = end;

        // If this is a keyword, return the appropriate token type
        if (curTokenText == "type") return Token(KW_TYPE, "");
        if (curTokenText == "int") return Token(KW_INT, "");
        else return Token(ID, curTokenText);   // Otherwise, return an identifier token
    } 

    // If the current character is numeric, it's a number literal
    else if (isNumeric(*bufferPtr)) {
        const char* end = bufferPtr + 1;
        while(isNumeric(*end)) end++;

        // Get the text of the number literal
        llvm::StringRef numberLiteral(bufferPtr, end - bufferPtr);
        
        // Update the buffer pointer
        bufferPtr = end;

        // Return a number literal token
        return Token(NUM, numberLiteral);
    }

    // If the current character is not a letter or a number, it must be an operator or punctuation
    Token result(UNKNOWN, "");

    switch (*bufferPtr) {

        // Handle each operator/punctuation character and return the appropriate token type
        case '+': {
            result = Token(PLUS, "");
            break;
        }
        case '-': {
            result = Token(MINUS, "");  
            break;
        }
        case '*': {
            result = Token(STAR, "");
            break;
        } 
        case '/': {
            result = Token(SLASH, "");
            break;
        } 
        case '(': {
            result = Token(LEFT_PAR, "");
            break;
        } 
        case ')': {
            result = Token(RIGHT_PAR, "");
            break;
        } 
        case ';': {
            result = Token(SEMICOLON, "");
            break;
        } 
        case '=': {
            result = Token(EQUAL, "");
            break;
        } 
        case ',': {
            result = Token(COMMA, "");
            break;
        } 
        default :
    }

    // Update the buffer pointer and return the token
    bufferPtr++;
    return result;
}

