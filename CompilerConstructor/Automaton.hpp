
#ifndef AUTOMATON_HPP
#define AUTOMATON_HPP

#include <list>
#include <Token.hpp>

class Edge;

class State {
    public:
    State(std::string ID, bool inGoal=false);
    Edge* addEdge(std::string ID, bool negate);
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
    Edge(std::string ID, bool negate);
    void setNext(State* next);
    State* getNext();
    std::string getID();
    char getChar();
    bool negate;

    private:
    std::string ID;
    State* nextState;
    char transChar;
};

class Automaton {
    public:
    Automaton(Token* token, std::string startID);
    void reset();
    void update(char input);
    void addStateTransition(
        std::string fromStateID, std::string toStateID, char transChar, bool negate=false, bool isGoal=false);
    void revert();
    bool isOnGoal();
    bool isDead();
    Token* getToken();

    private:
    Token* token;
    State* start;
    std::list<State*>* currents;
    std::list<State*>* prevs;
};

#endif
