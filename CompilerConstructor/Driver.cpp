
#include "Driver.hpp"
#include <iostream>
#include <fstream>

Driver::Driver(std::string lexFile, std::string syntaxFile) {
    std::cout << "Entered Driver\n";

    std::ifstream inLexFile(lexFile);
    lexer = new Lexer(Tokenize(&inLexFile));

    std::cout << "Successfully Built Lexer\n";

    std::ifstream inSyntaxFile(syntaxFile);
    syntaxer = new Syntaxer(Tokenize(&inSyntaxFile));

    std::cout << "Successfully Built Syntaxer\n";
}
void Driver::run(char* BBCFile) {
    std::ifstream inBBCFile(BBCFile);
    std::string temp;
    while (getline(inBBCFile, temp)) {
        rawProgramText += temp;
        rawProgramText += '\n';
    }

    lexer->lex(rawProgramText);
    std::cout << "Successfully Lexed\n";
    lexer->printTokenstream();
}
std::list<std::string> Driver::Tokenize(std::ifstream* specFile) {
    // break into tokens
    std::list<std::string> tokens;
    std::string token;
    while (specFile->good()) {
        (*specFile) >> token;
        tokens.push_back(token);
    }
    return tokens;
}
