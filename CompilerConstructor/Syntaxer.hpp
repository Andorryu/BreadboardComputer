
#ifndef SYNTAXER_HPP
#define SYNTAXER_HPP

#include <list>
#include <string>
#include "Automaton.hpp"

class ASTNode {
    public:
    ASTNode();
};

class Syntaxer {
    public:
    Syntaxer(std::list<std::string> sddTokens, const std::list<Automaton*>* automata);
    void ParseSDD();
};

#endif
