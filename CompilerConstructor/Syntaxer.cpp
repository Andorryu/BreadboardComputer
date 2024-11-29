
#include "Syntaxer.hpp"
#include "SDD.hpp"

// Syntaxer
// public
Syntaxer::Syntaxer(std::list<std::string>* sddTokens, std::list<Token>* lexerTokens) {
    // create list of known ProdNodes
    sdd = new SDD();
    // start filling productions
    for (auto sddtok = sddTokens->begin(); sddtok != sddTokens->end(); sddtok++) {
        // new production
        if (*sddtok == "nl") {
            sddtok++;
            
        }
    }
}

void Syntaxer::ParseSDD() {
    
}