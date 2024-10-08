
#ifndef AUTOMATON_HPP
#define AUTOMATON_HPP

#include <list>
#include <Token.hpp>

class Edge;

class State {
    public:
    State(std::string ID, bool inGoal=false);
    Edge* addEdge(std::string ID);
    std::list<Edge*>* getImmEdgesByChar(char ID);
    State* findStateByID(std::string ID);
    std::string getID();
    bool isGoal();

    private:
    std::string ID;
    std::list<Edge*>* edges;
    bool goal;
};

class Edge {
    public:
    Edge(std::string ID);
    void setNext(State* next);
    State* getNext();
    std::string getID();
    char getChar();

    private:
    std::string ID;
    State* nextState;
    char transChar;
    bool negate;
    bool isAlpha;
    bool isNum;
};

class Automaton {
    public:
    Automaton(Token token, std::string startStateID="S");
    void update(char input);
    void Automaton::addStateTransition(
        std::string fromStateID, std::string toStateID, char transChar, bool inGoal=false);
    bool isOnGoal();
    bool isDead();

    private:
    Token token;
    State* start;
    std::list<State*>* currents;
    std::list<State*>* prevs;
};

#endif
