
#include <Lexer.hpp>
#include <iostream>

// public
Lexer::Lexer(std::list<std::string> tokens) {

    // fill automata based on .nfa file tokens
    automata = std::list<Automaton*>();
    for (auto nfatok = tokens.begin(); nfatok != tokens.end(); nfatok++) {
        if (*nfatok == "\n") { // new automaton and start state
            nfatok++;
            automata.push_back(new Automaton(new Token(*nfatok), *(++nfatok)));
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
                for (char c = '0'; c <= '9'; c++) { // uppercase
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
    std::string tokenValue = "";
    Token* token;
    // run each new character on all automata
    for (int i = 0; i < raw.size(); i++) {
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
            token = findFirstInGoal()->getToken();
            token->setValue(tokenValue);
            tokenStream.push_back(token);
            tokenValue = "";
            resetAutomata();
            i--;
        }
        else {
            tokenValue += raw[i];
        }
    }
}
std::list<Token*> Lexer::getTokenStream() {
    return tokenStream;
}
void Lexer::print() {
    for (auto tok = tokenStream.begin(); tok != tokenStream.end(); tok++) {
        (*tok)->print();
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
}
