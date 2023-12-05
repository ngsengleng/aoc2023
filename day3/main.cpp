#include <iostream>
#include "part1.cpp"
#include "part2.cpp"
int main() {
    Part1 part1;
    Part2 part2;
    std::fstream f;
    f.open("../input3.txt");
    std::cout << part1.solve(f) << std::endl;
    f.close();
    f.open("../input3.txt");
    std::cout << part2.solve(f) << std::endl;
    f.close();
}
