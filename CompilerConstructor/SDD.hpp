
#ifndef SDD_HPP
#define SDD_HPP

#include <list>
#include <string>
#include "Production.hpp"


class SDD { // i.e., non-terminal rules
    public:
    SDD();
    void AddNewProduction();
    void AddProdNode(std::string prodNode);
    bool ProdNodeExists(std::string prodNode);

    private:
    std::list<Production*>* prods;
    std::list<ProdNode*>* cachedProdNodes;
};

#endif
