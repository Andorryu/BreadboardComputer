
#include "Token.hpp"
#include <iostream>

Token::Token(std::string ID) {
    this->ID = ID;
}
void Token::SetValue(std::string value) {
    this->value = value;
}
void Token::PrintID() {
    std::cout << ID;
}
void Token::Print() {
    std::cout << ID << ": " << value;
}
