#include <iostream>
#include "part1.cpp"
#include "part2.cpp"

int main() {
    std::fstream f;
    Part1 part1;
    f.open("../input4.txt");
    std::cout << part1.solve(f) << std::endl;
    f.close();
    Part2 part2;
    f.open("../input4.txt");
    std::cout << part2.solve(f) << std::endl;
    f.close();
}
