
#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <Automaton.hpp>
#include <Token.hpp>

class Tokenizer {

    public:
    // constructor initializes automata
    Tokenizer(std::list<Automaton*>* automata);

    private:
    std::list<Automaton*>* automata;
    // types
    Automaton* usignTypeAut;
    Automaton* signTypeAut;
    Automaton* charTypeAut;
    Automaton* boolTypeAut;
    Automaton* voidTypeAut;
    // other reserved words
    Automaton* ifAut;
    Automaton* elseAut;
    Automaton* whileAut;
    Automaton* displayAut;
    Automaton* classAut;
    Automaton* returnAut;
    // ID
    Automaton* identifierAut;
    // Expressions
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
    Automaton* assignAut;
    Automaton* equalsAut;
    Automaton* notEqualsAut;
    Automaton* greaterAut;
    Automaton* greaterEqAut;
    Automaton* lessAut;
    Automaton* lessEqAut;
    // Brackets
    Automaton* lparensAut;
    Automaton* rparensAut;
    Automaton* lcurlyAut;
    Automaton* rcurlyAut;
    Automaton* lbracketAut;
    Automaton* rbracketAut;
    // grammar
    Automaton* commaAut;
    Automaton* semicolonAut;
    Automaton* dotAut;
    Automaton* arrowAut;
    // literals
    Automaton* decIntLitAut;
    Automaton* binIntLitAut;
    Automaton* hexIntLitAut;
    Automaton* charLitAut;
    Automaton* boolLitAut;
};

#endif
