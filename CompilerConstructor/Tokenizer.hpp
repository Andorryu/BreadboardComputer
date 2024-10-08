
#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <Automaton.hpp>

class Tokenizer {

    public:
    // constructor initializes automata
    Tokenizer();

    private:
    Automaton* unsignAut;
    Automaton* signAut;
    Automaton* charAut;
    Automaton* boolAut;
    Automaton* identifierAut;
    Automaton* logAndAut;
    Automaton* logOrAut;
    Automaton* logNotAut;
    Automaton* bitAndAut;
    Automaton* bitOrAut;
    Automaton* bitNotAut;
    Automaton* crossAut;
    Automaton* dashAut;
    Automaton* starAut;
    Automaton* slashAut;
    Automaton* lparensAut;
    Automaton* rparensAut;
    Automaton* lcurlyAut;
    Automaton* rcurlyAut;
    Automaton* lbracketAut;
    Automaton* rbracketAut;
    Automaton* ifAut;
    Automaton* elseAut;
    Automaton* whileAut;
    Automaton* displayAut;
    Automaton* semicolonAut;
    Automaton* commaAut;
    Automaton* classAut;
    Automaton* returnAut;
};

#endif
