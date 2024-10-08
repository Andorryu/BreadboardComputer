
#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <Automaton.hpp>
#include <Token.hpp>

class Tokenizer {

    public:
    // constructor initializes automata
    Tokenizer(std::string spec);

    private:
    std::list<Automaton*>* automata;
};

#endif
