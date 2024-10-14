
#ifndef LEXER_HPP
#define LEXER_HPP

#include <Automaton.hpp>
#include <Token.hpp>

class Lexer {
    public:
    Lexer(std::list<std::string> tokens);
    void lex(std::string raw);
    std::list<Token*> getTokenStream();
    void print();

    private:
    bool allDead();
    void revertAutomata();
    void resetAutomata();
    Automaton* findFirstInGoal();
    std::list<Automaton*> automata;
    std::list<Token*> tokenStream;
};

#endif
