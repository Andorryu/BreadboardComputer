
#include "Token.hpp"
#include <iostream>

Token::Token(std::string ID, std::string value) {
    this->ID = ID;
    this->value = value;
}

void Token::Print() {
    std::cout << ID << " : " << value;
}

std::string Token::GetID()
{
    return this->ID;
}

std::string Token::GetValue()
{
    return this->value;
}
