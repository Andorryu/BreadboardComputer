
#ifndef AUTOMATA_HPP
#define AUTOMATA_HPP

class Edge;

class State {
    public:
    State(Edge* edges, int numEdges) { this->edges = edges; this->numEdges = numEdges; }
    Edge* getEdge(char id);

    private:
    int numEdges;
    Edge* edges;
};

class Edge {
    public:
    Edge(State* next, char edgeChar) { this->next = next; this->edgeChar = edgeChar; }
    State* getNext();

    private:
    State* next;
    char edgeChar;
};


class Automata {
    public:
    Automata(State* start) { this->start = start; }

    private:
    State* start;
};

#endif
