
#ifndef AUTOMATON_HPP
#define AUTOMATON_HPP

#include <list>
#include <Token.hpp>

class Edge;

class State {
    public:
    State(std::string ID);
    void addEdge(std::string ID);
    std::list<Edge*>* getEdgesByChar(char ID);
    Edge* getEdgeByID(std::string ID);

    private:
    std::string ID;
    std::list<Edge*>* edges;
    bool isGoal;
};

class Edge {
    public:
    Edge(std::string ID);
    State* getNext();
    std::string getID();
    char getChar();

    private:
    std::string ID;
    State* next;
    char transChar;
    bool negate;
    bool isAlpha;
    bool isNum;
};

class Automaton {
    public:
    Automaton(Token token);
    void update(char input);
    void addState(std::string edgeID, std::string fromEdge, bool isGoal);
    void addEdge(std::string ID, std::string fromState, std::string toState);
    bool isOnGoal();
    bool isDead();

    private:
    Token token;
    State* start;
    std::list<State*>* currents;
    std::list<State*>* prevs;
};

#endif
