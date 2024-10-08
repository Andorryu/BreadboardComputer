
#include <Driver.hpp>

// collect specifications
Driver::Driver(std::string lexFile, std::string grammarFile) {
    std::ifstream inLexFile(lexFile);
    std::string lexSpec;
    inLexFile >> lexSpec;
    buildTokenizer(lexSpec);
    inLexFile.close();

    std::ifstream inGrammarFile(grammarFile);
    std::string grammarSpec;
    inGrammarFile >> grammarSpec;
    buildTokenizer(grammarSpec);
    inGrammarFile.close();
}
void Driver::run() {
    
}
void Driver::buildTokenizer(std::string spec) {
    tokenizer = new Tokenizer(spec);
}
