#ifndef PRODUCTION_HPP
#define PRODUCTION_HPP
#include <list>
#include <string>

class ProdNode { // i.e., terminals and non-terminals
    public:
    ProdNode(std::string ID);
    std::string GetID();
    std::string GetType();

    private:
    std::string ID;
    std::string type;
};

class Production {
    public:
    Production();
    void SetHead(ProdNode* head);
    void AppendToRule(ProdNode* prodNode);
    ProdNode* GetHead();
    std::list<ProdNode*>* GetRule();

    private:
    ProdNode* head;
    std::list<ProdNode*>* rule;
};

#endif