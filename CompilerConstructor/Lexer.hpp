
#ifndef LEXER_HPP
#define LEXER_HPP

#include "Automaton.hpp"
#include "Token.hpp"

class Lexer {
    public:
    Lexer(std::list<std::string> tokens);
    void lex(std::string raw);
    std::list<Token> getTokenStream();
    void printNFATokens(std::list<std::string> tokens);
    void printTokenstream();

    private:
    bool allDead();
    void revertAutomata();
    void resetAutomata();
    Automaton* findFirstInGoal();
    void printCurrentAutomataStates();
    std::list<Automaton*> automata;
    std::list<Token> tokenStream;
    int line;
};

#endif
