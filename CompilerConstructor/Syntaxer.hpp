
#ifndef SYNTAXER_HPP
#define SYNTAXER_HPP

#include <list>
#include <string>
#include "Automaton.hpp"
#include "Token.hpp"

class ASTNode {
    public:
    ASTNode();
};

class Syntaxer {
    public:
    Syntaxer(std::list<std::string>* sddTokens, std::list<Token>* lexerTokens);
    void ParseSDD();
    
    private:
    SDD* sdd;
};

#endif
