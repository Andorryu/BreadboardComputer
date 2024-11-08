
#ifndef PRODUCTION_HPP
#define PRODUCTION_HPP

#include <list>
#include <string>

class ProdNode { // i.e., terminals and non-terminals
    public:
    ProdNode(std::string ID);

    private:
    std::string ID;
    std::string type;
};

class Production { // i.e., non-terminal rules
    public:
    Production();

    private:
    ProdNode* prodNode;
    std::list<std::list<ProdNode*>*>* defns;
};

#endif
