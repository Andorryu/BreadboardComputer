
#ifndef SYNTAXER_HPP
#define SYNTAXER_HPP

#include <list>
#include <string>

class ProdNode {
    public:
    ProdNode(std::string ID);

    private:
    std::string ID;
    std::string type;
};

class Production {
    public:
    Production();

    private:
    ProdNode* prodNode;
    std::list<ProdNode*>* defnNodes;
};

class ASTNode {
    public:
    ASTNode();
};

class Syntaxer {
    public:
    Syntaxer(std::list<std::string> tokens);
    void ParseSDD();
};

#endif
