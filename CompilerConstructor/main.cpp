
#include "Driver.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "format: bbc <input file>";
        return 0;
    }
    Driver("bbc.nfa", "bbc.gram").run(argv[1]);
}
