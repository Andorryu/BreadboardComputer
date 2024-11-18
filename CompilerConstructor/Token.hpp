
#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "Production.hpp"
#include <string>

class Token {
    public:
    Token(std::string ID, std::string value);
    void Print();
    std::string GetID();
    std::string GetValue();

    private:
    std::string ID;
    std::string value;
};

#endif
