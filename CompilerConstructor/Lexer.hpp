
#ifndef LEXER_HPP
#define LEXER_HPP

#include "Automaton.hpp"
#include "Token.hpp"

class Lexer {
    public:
    Lexer(std::list<std::string> tokens);
    void Lex(std::string raw);
    std::list<Token> GetTokenStream();
    void PrintNFATokens(std::list<std::string> tokens);
    void PrintTokenstream();

    private:
    bool AllDead();
    void RevertAutomata();
    void ResetAutomata();
    Automaton* FindFirstInGoal();
    void PrintCurrentAutomataStates();
    std::list<Automaton*> automata;
    std::list<Token> tokenStream;
    int line;
};

#endif
