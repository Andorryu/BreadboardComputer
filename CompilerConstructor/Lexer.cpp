
#include "Lexer.hpp"
#include <iostream>

// public
Lexer::Lexer(std::list<std::string> tokens) {
    line = 0;
    std::cout << "Building Automata\n";
    // fill automata based on .nfa file tokens
    automata = std::list<Automaton*>();
    for (auto nfatok = tokens.begin(); nfatok != tokens.end(); nfatok++) {
        if (*nfatok == "nl") { // new automaton and start state
            nfatok++;
            std::string id = *nfatok;
            automata.push_back(new Automaton(new Token(id), *(++nfatok)));
            nfatok--;
        } else { // state and transition
            std::string fromState = *nfatok; // get fromState
            nfatok++;
            // negate?
            bool negate = false;
            if (*nfatok == "not") {
                negate = true;
                nfatok++;
            }
            // get toState
            nfatok++;
            std::string toState;
            bool isGoal = false;
            if ((*nfatok)[(*nfatok).size()-1] == '+') {
                toState = (*nfatok).substr(0, (*nfatok).size()-1);
                isGoal = true;
            } else {
                toState = *nfatok;
            }
            nfatok--;

            // get transChar/add transition
            if (*nfatok == "alpha") { // upper or lower case characters
                for (char c = 'a'; c <= 'z'; c++) { // lowercase
                    automata.back()->addStateTransition(fromState, toState, c, negate, isGoal);
                }
                for (char c = 'A'; c <= 'Z'; c++) { // uppercase
                    automata.back()->addStateTransition(fromState, toState, c, negate, isGoal);
                }
            } else if (*nfatok == "num") { // 0-9
                for (char c = '0'; c <= '9'; c++) { // numerical
                    automata.back()->addStateTransition(fromState, toState, c, negate, isGoal);
                }
            } else {
                char transChar;
                if (*nfatok == "epsilon") {
                    transChar = '\0';
                } else if (*nfatok == "\\n") {
                    transChar = '\n';
                } else {
                    transChar = (*nfatok)[0];
                }
                automata.back()->addStateTransition(fromState, toState, transChar, negate, isGoal);
            }
            nfatok++;
        }
    }
}
void Lexer::lex(std::string raw) {
    // std::cout << "Running Lexer on input:\n" << raw << "\n";
    std::string tokenValue = "";
    Token* token;

    // run each new character on all automata
    for (int i = 0; i < raw.size(); i++) {

        if (raw[i] == '\n') {
            line++;
        }

        // std::cout << "(" << tokenValue << ") " << ((raw[i] == '\n') ? "\\n" : std::string(1, raw[i])) << "\n";

        // update all automata
        for (auto atmtn = automata.begin(); atmtn != automata.end(); atmtn++) {
            (*atmtn)->update(raw[i]);
        }

        // revert if dead and find the first automaton that is in a goal state
        if (allDead()) {
            // if whitespace alone causes automata to die, ignore it
            if (tokenValue == "" && (raw[i] == ' ' || raw[i] == '\n')) {
                resetAutomata();
                continue;
            }
            revertAutomata();
            // printCurrentAutomataStates();
            Automaton* first = findFirstInGoal();
            if (first == nullptr) {
                std::cerr << "LEXICAL ERROR: char " << raw[i] << " on line " << line << "\n";
                return;
            }
            token = first->getToken();
            token->setValue(tokenValue);
            tokenStream.push_back(*token);
            tokenValue = "";
            resetAutomata();
            // std::cout << "found token! "; token->printID(); std::cout << "\n";
            i--;
        }
        else {
            tokenValue += raw[i];
        }
    }
}
std::list<Token> Lexer::getTokenStream() {
    return tokenStream;
}
void Lexer::printNFATokens(std::list<std::string> tokens) {
    for (auto tok = tokens.begin(); tok != tokens.end(); tok++) {
        std::cout << *tok << " ";
    }
    std::cout << "\n";
}
void Lexer::printTokenstream() {
    for (auto tok = tokenStream.begin(); tok != tokenStream.end(); tok++) {
        (*tok).print();
        std::cout << "\n";
    }
}
// private
bool Lexer::allDead() {
    for (auto atmtn = automata.begin(); atmtn != automata.end(); atmtn++) {
        if (!(*atmtn)->isDead()) {
            return false;
        }
    }
    return true;
}
void Lexer::revertAutomata() {
    for (auto atmtn = automata.begin(); atmtn != automata.end(); atmtn++) {
        (*atmtn)->revert();
    }
}
void Lexer::resetAutomata() {
    for (auto atmtn = automata.begin(); atmtn != automata.end(); atmtn++) {
        (*atmtn)->reset();
    }
}
Automaton* Lexer::findFirstInGoal() {
    for (auto atmtn = automata.begin(); atmtn != automata.end(); atmtn++) {
        if ((*atmtn)->isOnGoal()) {
            return *atmtn;
        }
    }
    return nullptr;
}
void Lexer::printCurrentAutomataStates() {
    for (auto atmtn = automata.begin(); atmtn != automata.end(); atmtn++) {
        if (!(*atmtn)->isDead()) {
            std::cout << "    (";
            (*atmtn)->getToken()->printID();
            std::cout << "): ";
            (*atmtn)->printCurrent();
            std::cout << "\n";
        }
    }
}
