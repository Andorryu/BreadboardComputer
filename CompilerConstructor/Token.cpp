
#include "Token.hpp"
#include <iostream>

Token::Token(std::string ID) {
    this->ID = ID;
}
void Token::setValue(std::string value) {
    this->value = value;
}
void Token::printID() {
    std::cout << ID;
}
void Token::print() {
    std::cout << ID << ": " << value;
}
