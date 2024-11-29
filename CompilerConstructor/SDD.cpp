
#include "SDD.hpp"

// Production
// public
SDD::SDD() {
    prods = new std::list<Production*>();
    cachedProdNodes = new std::list<ProdNode*>();
}

void SDD::AddNewProduction() {
    prods->push_back(new Production());
}

void SDD::AddProdNode(std::string prodNodeID) {
    ProdNode* prodNode = nullptr;
    if (!ProdNodeExists(prodNodeID)) {
        prodNode = new ProdNode(prodNodeID);
        cachedProdNodes->push_back(prodNode);
        
    }
    else {

    }
}

bool SDD::ProdNodeExists(std::string prodNodeID) {
    for (ProdNode* tmpNode : *cachedProdNodes) {
        if (tmpNode->GetID() == prodNodeID) {
            return true;
        }
    }
    return false;
}
