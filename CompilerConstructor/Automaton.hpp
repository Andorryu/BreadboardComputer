
#ifndef AUTOMATON_HPP
#define AUTOMATON_HPP

#include <list>
#include <string>

class Edge;

class State {
    public:
    State(std::string ID, bool inGoal);
    Edge* addEdge(std::string ID, char transChar, bool negate);
    std::list<Edge*>* getImmEdgesByChar(char ID);
    State* findStateByID(std::string ID, std::list<std::string>* visitedIDs);
    std::string getID();
    bool isGoal();
    void print();

    private:
    std::string ID;
    std::list<Edge*>* edges;
    bool goal;
};

class Edge {
    public:
    Edge(std::string ID, char transChar, bool negate);
    void SetNext(State* next);
    State* GetNext();
    std::string GetID();
    char GetChar();
    bool negate;

    private:
    std::string ID;
    State* nextState;
    char transChar;
};

class Automaton {
    public:
    Automaton(std::string ID, std::string startID);
    void Reset();
    void Update(char input);
    void AddStateTransition(
        std::string fromStateID, std::string toStateID, char transChar, bool negate, bool isGoal);
    void Revert();
    bool IsOnGoal();
    bool IsDead();
    std::string GetID();
    void PrintCurrent();

    private:
    std::string ID;
    State* start;
    std::list<State*>* currents;
    std::list<State*>* prevs;
};

#endif
