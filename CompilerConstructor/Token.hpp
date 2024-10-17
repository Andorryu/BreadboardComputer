
#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

class Token {
    public:
    Token(std::string ID);
    void SetValue(std::string value);
    void PrintID();
    void Print();

    private:
    std::string ID;
    std::string value;
};

#endif
