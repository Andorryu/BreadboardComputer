
#include "Automaton.hpp"
#include <iostream>

// State
State::State(std::string ID, bool inGoal=false) {
    this->ID = ID;
    edges = new std::list<Edge*>();
    goal = inGoal;
}
Edge* State::addEdge(std::string ID, char transChar, bool negate) {
    edges->push_back(new Edge(ID, transChar, negate));
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
State* State::findStateByID(std::string ID, std::list<std::string>* visitedIDs) {
    // check if state has been visited already
    for (auto id = visitedIDs->begin(); id != visitedIDs->end(); id++) {
        if (ID == *id) {
            return nullptr;
        }
    }
    // note that this state has been visited
    visitedIDs->push_back(this->ID);
    
    // check if target ID matches this state's ID
    if (ID == this->ID) {
        return this;
    }
    // recurse for each edge's state
    for (auto edge : *edges) {
        State* nextState = edge->getNext()->findStateByID(ID, visitedIDs);
        if (nextState != nullptr) {
            return nextState;
        }
    }
    return nullptr;
}
std::string State::getID() {
    return ID;
}
bool State::isGoal() {
    return goal;
}
void State::print() {
    std::cout << ID;
}

// Edge
Edge::Edge(std::string ID, char transChar, bool negate) {
    this->ID = ID;
    nextState = nullptr;
    this->transChar = transChar;
    this->negate = negate;
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
    std::list<State*>* temp = new std::list<State*>();
    while (!currents->empty()) {
        charEdges = currents->front()->getImmEdgesByChar(input);

        for (auto j = charEdges->begin(); j != charEdges->end(); j++) {
            temp->push_back((*j)->getNext());
        }
        prevs->push_back(currents->front());
        currents->pop_front();
    }
    // add new states to currents
    currents = temp;
}
// add a new edge and attach it from fromStateID to toStateID.
// if state with ID toStateID does not exist, create a new state with ID toStateID.
void Automaton::addStateTransition(
    std::string fromStateID, std::string toStateID, char transChar, bool negate=false, bool isGoal=false) {

    State* fromState = start->findStateByID(fromStateID, new std::list<std::string>());
    if (fromState == nullptr) {
        std::cerr << "ERROR " << "("; token->print(); std::cerr << ")" << ": State with ID " << fromStateID << " does not exist.\n";
        return;
    }

    State* toState = start->findStateByID(toStateID, new std::list<std::string>());

    if (toState != nullptr) {
        fromState->addEdge(fromStateID + transChar + toStateID, transChar, negate)->setNext(toState);
    } else {
        fromState->addEdge(fromStateID + transChar + toStateID, transChar, negate)->setNext(new State(toStateID, isGoal));
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
Token* Automaton::getToken() {
    return token;
}
void Automaton::printCurrent() {
    for (auto state = currents->begin(); state != currents->end(); state++) {
        (*state)->print();
        std::cout << "  ";
    }
}
