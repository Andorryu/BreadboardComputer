
#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

class Token {
    public:
    Token(std::string ID);
    void setValue(std::string value);
    void print();

    private:
    std::string ID;
    std::string value;
};

#endif
