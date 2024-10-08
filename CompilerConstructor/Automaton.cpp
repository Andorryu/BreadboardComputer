
#include <Automaton.hpp>

// State
Edge* State::getEdge(char id) {
    for (int i = 0; i < numEdges; i++) {
        if (edges[i].getChar() == id) {
            return &(edges[i]);
        }
    }
    return nullptr;
}
int State::getNumEdges() {
    return numEdges;
}
// Edge
State* Edge::getNext() {
    return next;
}
char Edge::getChar() {
    return edgeChar;
}
// Automaton
void Automaton::update(char input) {
    for (auto curState : *currents) {
        for (int j = 0; j < curState->getNumEdges(); j++) {
            if (curState->getEdge(input) != nullptr) {

            } else if (curState->getEdge('\0') != nullptr) { // epsilon check

            } else {

            }
        }
    }
}
bool Automaton::isGoal() {
    for (auto curState : *currents) {
        if (curState == goal) {
            return true;
        }
    }
    return false;
}
