#include <iostream>
#include "part1.cpp"
#include "part2.cpp"

int main() {
    Part1 part1;
    std::fstream f;
    f.open("../input2.txt");
    std::cout << part1.solve(f) << std::endl;
    f.close();
    f.open("../input2.txt");
    Part2 part2;
    std::cout << part2.solve(f) << std::endl;
    f.close();
}
