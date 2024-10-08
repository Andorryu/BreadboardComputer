#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <string>
#include <fstream>
#include <Tokenizer.hpp>

class Driver {
    public:
    Driver(std::string lexFile, std::string grammarFile);
    void run();

    private:
    void buildTokenizer(std::string spec);
    Tokenizer* tokenizer;
};

#endif
