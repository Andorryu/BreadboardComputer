
#include "Lexer.hpp"
#include <iostream>

// public
Lexer::Lexer(std::list<std::string>* tokens) {
    line = 0;
    std::cout << "Building Automata\n";
    // fill automata based on .nfa file tokens
    automata = new std::list<Automaton*>();
    for (auto nfatok = tokens->begin(); nfatok != tokens->end(); nfatok++) {
        if (*nfatok == "nl") { // new automaton and start state
            nfatok++;
            std::string id = *nfatok;
            automata->push_back(new Automaton(id, *(++nfatok)));
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
                    automata->back()->AddStateTransition(fromState, toState, c, negate, isGoal);
                }
                for (char c = 'A'; c <= 'Z'; c++) { // uppercase
                    automata->back()->AddStateTransition(fromState, toState, c, negate, isGoal);
                }
            } else if (*nfatok == "num") { // 0-9
                for (char c = '0'; c <= '9'; c++) { // numerical
                    automata->back()->AddStateTransition(fromState, toState, c, negate, isGoal);
                }
            } else {
                char transChar;
                if (*nfatok == "epsilon") {
                    transChar = '\0';
                } else if (*nfatok == "\\n") {
                    transChar = '\n';
                } else if ((*nfatok).size() == 1) {
                    transChar = (*nfatok)[0];
                } else {
                    std::cerr << "ERROR: Invalid transition character in nfa file\n";
                    exit(0);
                }
                automata->back()->AddStateTransition(fromState, toState, transChar, negate, isGoal);
            }
            nfatok++;
        }
    }
}
void Lexer::Lex(std::string raw) {
    // std::cout << "Running Lexer on input:\n" << raw << "\n";
    std::string tokenValue = "";
    tokenStream = new std::list<Token*>();

    // run each new character on all automata
    for (int i = 0; i < raw.size(); i++) {

        if (raw[i] == '\n') {
            line++;
        }

        // std::cout << "(" << tokenValue << ") " << ((raw[i] == '\n') ? "\\n" : std::string(1, raw[i])) << "\n";

        // update all automata
        for (auto atmtn = automata->begin(); atmtn != automata->end(); atmtn++) {
            (*atmtn)->Update(raw[i]);
        }

        // revert if dead and find the first automaton that is in a goal state
        if (AllDead()) {
            // if whitespace alone causes automata to die, ignore it
            if (tokenValue == "" && (raw[i] == ' ' || raw[i] == '\n')) {
                ResetAutomata();
                continue;
            }
            RevertAutomata();
            // printCurrentAutomataStates();
            Automaton* first = FindFirstInGoal();
            if (first == nullptr) {
                std::cerr << "LEXICAL PARSING ERROR: char " << raw[i] << " on line " << line << "\n";
                exit(1);
            }
            auto t = new Token(first->GetID(), tokenValue);
            tokenStream->push_back(t);
            tokenValue = "";
            ResetAutomata();
            // std::cout << "found token! "; token->printID(); std::cout << "\n";
            i--;
        }
        else {
            tokenValue += raw[i];
        }
    }
}
std::list<Token*>* Lexer::GetTokenStream() {
    return tokenStream;
}
std::list<std::string>* Lexer::GetTokens() {
    return new std::list<std::string>();
}
void Lexer::PrintNFATokens(std::list<std::string> tokens) {
    for (auto tok = tokens.begin(); tok != tokens.end(); tok++) {
        std::cout << *tok << " ";
    }
    std::cout << "\n";
}
void Lexer::PrintTokenstream() {
    for (auto tok = tokenStream->begin(); tok != tokenStream->end(); tok++) {
        (*tok)->Print();
        std::cout << "\n";
    }
}
void Lexer::PrintTokens() {

}
// private
bool Lexer::AllDead() {
    for (auto atmtn = automata->begin(); atmtn != automata->end(); atmtn++) {
        if (!(*atmtn)->IsDead()) {
            return false;
        }
    }
    return true;
}
void Lexer::RevertAutomata() {
    for (auto atmtn = automata->begin(); atmtn != automata->end(); atmtn++) {
        (*atmtn)->Revert();
    }
}
void Lexer::ResetAutomata() {
    for (auto atmtn = automata->begin(); atmtn != automata->end(); atmtn++) {
        (*atmtn)->Reset();
    }
}
Automaton* Lexer::FindFirstInGoal() {
    for (auto atmtn = automata->begin(); atmtn != automata->end(); atmtn++) {
        if ((*atmtn)->IsOnGoal()) {
            return *atmtn;
        }
    }
    return nullptr;
}
void Lexer::PrintCurrentAutomataStates() {
    for (auto atmtn = automata->begin(); atmtn != automata->end(); atmtn++) {
        if (!(*atmtn)->IsDead()) {
            std::cout << "    (" << (*atmtn)->GetID() << "): ";
            (*atmtn)->PrintCurrent();
            std::cout << "\n";
        }
    }
}
