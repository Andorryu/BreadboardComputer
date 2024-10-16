
#include "Driver.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "format: bbc <input .bbc> <input .nfa> <input .gram>";
        return 0;
    }
    Driver(argv[2], argv[3]).run(argv[1]);
}
