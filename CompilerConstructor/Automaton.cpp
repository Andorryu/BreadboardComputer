
#include <Automaton.hpp>

// State
State::State(std::string ID) {
    this->ID = ID;
    edges = new std::list<Edge*>();
    isGoal = false;
}
void State::addEdge(std::string ID) {
    edges->push_back(new Edge(ID));
}
std::list<Edge*>* State::getEdgesByChar(char transChar) {
    std::list<Edge*>* result = new std::list<Edge*>();
    for (std::list<Edge*>::iterator i = edges->begin(); i != edges->end(); i++) {
        if ((*i)->getChar() == transChar) {
            result->push_back(*i);
        }
    }
}
Edge* State::getEdgeByID(std::string ID) {
    for (auto edge : *edges) {
        if (edge->getID() == ID) {
            return edge;
        }
    }
}

// Edge
Edge::Edge(std::string ID) {
    this->ID = ID;
    next = nullptr;
    transChar = '\0';
    negate = false;
    isAlpha = false;
    isNum = false;
}
std::string Edge::getID() {
    return ID;
}
char Edge::getChar() {
    return transChar;
}
State* Edge::getNext() {
    return next;
}

// Automaton
Automaton::Automaton(Token token) {
    token = token;
    start = nullptr;
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
        epsilonEdges = (*i)->getEdgesByChar('\0'); // follow epsilon edges as far as needed

        for (j = epsilonEdges->begin(); j != epsilonEdges->end(); j++) {
            currents->push_back((*j)->getNext());
        }
    }

    // take all char edges from current states and delete state
    std::list<State*>::iterator end = currents->end();
    for (i = currents->begin(); i != end; i++) {
        charEdges = (*i)->getEdgesByChar(input);
        
        for (j = charEdges->begin(); j != charEdges->end(); j++) {
            currents->push_back((*j)->getNext());
        }
        prevs->push_front(*i);
        currents->remove(*i);
    }
}
void addState(std::string ID, std::string fromEdge, bool isGoal) {
    // search thru automaton for fromEdge
    
}
bool Automaton::isOnGoal() {

}
bool Automaton::isDead() {
    return currents->empty();
}
