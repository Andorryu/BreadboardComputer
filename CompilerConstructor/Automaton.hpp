
#ifndef AUTOMATON_HPP
#define AUTOMATON_HPP

#include <list>

class Edge;

class State {
    public:
    State(Edge* edges, int numEdges) { this->edges = edges; this->numEdges = numEdges; }
    Edge* getEdge(char id);
    int getNumEdges();

    private:
    int numEdges;
    Edge* edges;
};

class Edge {
    public:
    Edge(State* next, char edgeChar) { this->next = next; this->edgeChar = edgeChar; }
    State* getNext();
    char getChar();

    private:
    State* next;
    char edgeChar;
};


class Automaton {
    public:
    Automaton(State* start) { this->start = start; }
    void update(char input);
    bool isGoal();

    private:
    State* start;
    std::list<State*>* currents;
    State* goal;
    int numCurrents;
};

#endif
