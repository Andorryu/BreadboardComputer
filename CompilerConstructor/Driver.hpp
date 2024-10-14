#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <string>
#include <fstream>
#include <Lexer.hpp>
#include <Syntaxer.hpp>

class Driver {
    public:
    Driver(std::string lexFile, std::string grammarFile);
    void run();

    private:
    std::list<std::string> Tokenize(std::string spec);
    Lexer* lexer;
    Syntaxer* syntaxer;
};

#endif
