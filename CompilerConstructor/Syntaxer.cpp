
#include "Syntaxer.hpp"
#include "Production.hpp"

// Syntaxer
// public
Syntaxer::Syntaxer(std::list<std::string>* sddTokens, std::list<std::string>* lexerTokens) {
    // create list of known ProdNodes
    std::list<ProdNode> knownProdNodes = std::list<ProdNode>();
    // fill with tokens
    for (auto ltok = lexerTokens->begin(); ltok != lexerTokens->end(); ltok++) {
        knownProdNodes.push_back(ProdNode(*ltok));
    }
}

void Syntaxer::ParseSDD() {
    
}