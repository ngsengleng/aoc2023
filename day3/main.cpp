#include <iostream>
#include "part1.cpp"

int main() {
    Part1 part1;
    std::fstream f;
    f.open("../input3.txt");
    std::cout << part1.solve(f) << std::endl;
}
