
#include <Automaton.hpp>
#include <iostream>

// State
State::State(std::string ID, bool inGoal=false) {
    this->ID = ID;
    edges = new std::list<Edge*>();
    goal = inGoal;
}
Edge* State::addEdge(std::string ID) {
    edges->push_back(new Edge(ID));
    return edges->back();
}
std::list<Edge*>* State::getImmEdgesByChar(char transChar) {
    std::list<Edge*>* result = new std::list<Edge*>();
    for (std::list<Edge*>::iterator i = edges->begin(); i != edges->end(); i++) {
        if ((*i)->getChar() == transChar) {
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
Edge::Edge(std::string ID) {
    this->ID = ID;
    nextState = nullptr;
    transChar = '\0';
    negate = false;
    isAlpha = false;
    isNum = false;
}
void Edge::setNext(State* next) {
    nextState = next;
}
std::string Edge::getID() {
    return ID;
}
char Edge::getChar() {
    return transChar;
}
State* Edge::getNext() {
    return nextState;
}

// Automaton
Automaton::Automaton(Token token, std::string startStateID="S") {
    token = token;
    start = new State(startStateID);
    currents = new std::list<State*>();
    prevs = new std::list<State*>();
}
void Automaton::update(char input) {
    prevs = new std::list<State*>();
    std::list<Edge*>* charEdges;
    std::list<Edge*>* epsilonEdges;
    std::list<State*>::iterator i;
    std::list<Edge*>::iterator j;

    // take epsilon edges first
    for (i = currents->begin(); i != currents->end(); i++) {
        epsilonEdges = (*i)->getImmEdgesByChar('\0'); // follow epsilon edges as far as needed

        for (j = epsilonEdges->begin(); j != epsilonEdges->end(); j++) {
            currents->push_back((*j)->getNext());
        }
    }

    // take all char edges from current states and delete state
    std::list<State*>::iterator end = currents->end();
    for (i = currents->begin(); i != end; i++) {
        charEdges = (*i)->getImmEdgesByChar(input);
        
        for (j = charEdges->begin(); j != charEdges->end(); j++) {
            currents->push_back((*j)->getNext());
        }
        prevs->push_front(*i);
        currents->remove(*i);
    }
}
// add a new edge and attach it from fromStateID to toStateID.
// if state with ID toStateID does not exist, create a new state with ID toStateID.
void Automaton::addStateTransition(
    std::string fromStateID, std::string toStateID, char transChar, bool inGoal=false) {
        
    State* fromState = start->findStateByID(fromStateID);
    if (fromState == nullptr) {
        std::cerr << "ERROR: State with ID " << fromStateID << " does not exist.\n";
        return;
    }

    State* toState = start->findStateByID(toStateID);

    if (toState != nullptr) {
        fromState->addEdge(fromStateID + transChar + toStateID)->setNext(toState);
    } else {
        fromState->addEdge(fromStateID + transChar + toStateID)->setNext(new State(toStateID, inGoal));
    }
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
