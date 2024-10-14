
#include <Driver.hpp>

Driver::Driver(std::string lexFile, std::string syntaxFile) {
    std::ifstream inLexFile(lexFile);
    std::string lexSpec;
    inLexFile >> lexSpec;
    lexer = new Lexer(Tokenize(lexSpec));
    inLexFile.close();

    std::ifstream inSyntaxFile(syntaxFile);
    std::string grammarSpec;
    inSyntaxFile >> grammarSpec;
    syntaxer = new Syntaxer(Tokenize(grammarSpec));
    inSyntaxFile.close();
}
void Driver::run() {
    lexer->lex("hello");
    lexer->print();
}
std::list<std::string> Driver::Tokenize(std::string spec) {
    // break into tokens
    std::list<std::string> tokens;
    std::string token = "";
    for (int i = 0; i < spec.size(); i++) {
        // get tokens
        if (spec[i] == '\n') {
            token = "\n";
        }
        if (!(spec[i] == ' ' || spec[i] == '\0')) {
            token += spec[i];
            continue;
        }
        tokens.push_back(token);
        token = "";
    }
    return tokens;
}

