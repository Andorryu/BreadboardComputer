
#include <Automaton.hpp>
#include <iostream>

// State
State::State(std::string ID, bool inGoal=false) {
    this->ID = ID;
    edges = new std::list<Edge*>();
    goal = inGoal;
}
Edge* State::addEdge(std::string ID, bool negate) {
    edges->push_back(new Edge(ID, negate));
    return edges->back();
}
std::list<Edge*>* State::getImmEdgesByChar(char transChar) {
    std::list<Edge*>* result = new std::list<Edge*>();
    for (std::list<Edge*>::iterator i = edges->begin(); i != edges->end(); i++) {
        if ((*i)->getChar() == transChar && !(*i)->negate) {
            result->push_back(*i);
        } else if ((*i)->getChar() != transChar && (*i)->negate) {
            result->push_back(*i);
        }
    }
    return result;
}
State* State::findStateByID(std::string ID) {
    for (auto edge : *edges) {
        if (edge->getNext()->getID() == ID) {
            return edge->getNext();
        }
        else {
            return edge->getNext()->findStateByID(ID);
        }
    }
    return nullptr;
}
bool State::isGoal() {
    return goal;
}

// Edge
Edge::Edge(std::string ID, bool negate) {
    this->ID = ID;
    nextState = nullptr;
    transChar = '\0';
    negate = negate;
}
void Edge::setNext(State* next) {
    nextState = next;
}
State* Edge::getNext() {
    return nextState;
}
std::string Edge::getID() {
    return ID;
}
char Edge::getChar() {
    return transChar;
}

// Automaton
Automaton::Automaton(Token* token, std::string startID) {
    start = new State(startID);
    this->token = token;
    currents = new std::list<State*>();
    currents->push_back(start);
    prevs = new std::list<State*>();
}
void Automaton::reset() {
    currents = new std::list<State*>();
    currents->push_back(start);
    prevs = new std::list<State*>();
}
void Automaton::update(char input) {
    prevs = new std::list<State*>();
    std::list<Edge*>* charEdges;
    std::list<Edge*>* epsilonEdges;

    // take epsilon edges first
    for (auto i = currents->begin(); i != currents->end(); i++) {
        epsilonEdges = (*i)->getImmEdgesByChar('\0'); // follow epsilon edges as far as needed

        for (auto j = epsilonEdges->begin(); j != epsilonEdges->end(); j++) {
            currents->push_back((*j)->getNext());
        }
    }

    // take all char edges from current states and delete state
    std::list<State*>::iterator end = currents->end();
    for (auto i = currents->begin(); i != end; i++) {
        charEdges = (*i)->getImmEdgesByChar(input);
        
        for (auto j = charEdges->begin(); j != charEdges->end(); j++) {
            currents->push_back((*j)->getNext());
        }
        prevs->push_front(*i);
        currents->remove(*i);
    }
}
// add a new edge and attach it from fromStateID to toStateID.
// if state with ID toStateID does not exist, create a new state with ID toStateID.
void Automaton::addStateTransition(
    std::string fromStateID, std::string toStateID, char transChar, bool negate=false, bool isGoal=false) {
        
    State* fromState = start->findStateByID(fromStateID);
    if (fromState == nullptr) {
        std::cerr << "ERROR: State with ID " << fromStateID << " does not exist.\n";
        return;
    }

    State* toState = start->findStateByID(toStateID);

    if (toState != nullptr) {
        fromState->addEdge(fromStateID + transChar + toStateID, negate)->setNext(toState);
    } else {
        fromState->addEdge(fromStateID + transChar + toStateID, negate)->setNext(new State(toStateID, isGoal));
    }
}
void Automaton::revert() {
    currents = prevs;
    prevs = new std::list<State*>();
}
bool Automaton::isOnGoal() {
    for (auto state : *currents) {
        if (state->isGoal()) {
            return true;
        }
    }
    return false;
}
bool Automaton::isDead() {
    return currents->empty();
}
