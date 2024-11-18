
#include "Driver.hpp"
#include <iostream>
#include <fstream>

Driver::Driver(std::string lexFile, std::string syntaxFile) {
    std::cout << "Entered Driver\n";

    std::ifstream inLexFile(lexFile);
    lexer = new Lexer(Tokenize(&inLexFile));

    std::cout << "Successfully Built Lexer\n";

    std::ifstream inSyntaxFile(syntaxFile);
    syntaxer = new Syntaxer(Tokenize(&inSyntaxFile), lexer->GetTokens());

    std::cout << "Successfully Built Syntaxer\n";
}
void Driver::Run(char* BBCFile) {
    std::ifstream inBBCFile(BBCFile);
    std::string temp;
    while (getline(inBBCFile, temp)) {
        rawProgramText += temp;
        rawProgramText += '\n';
    }

    // lexing
    lexer->Lex(rawProgramText);
    std::cout << "Successfully Lexed\n\nToken Stream:\n";
    lexer->PrintTokenstream();

    // syntax

    // name checking

    // type checking

}
std::list<std::string>* Driver::Tokenize(std::ifstream* specFile) {
    // break into tokens
    std::list<std::string>* tokens = new std::list<std::string>();
    std::string token;
    while (specFile->good()) {
        (*specFile) >> token;
        tokens->push_back(token);
    }
    return tokens;
}
