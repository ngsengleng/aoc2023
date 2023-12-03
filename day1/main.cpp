#include <iostream>
#include "part1.cpp"
#include "part2.cpp"

int main() {
    std::fstream input1;
    input1.open("inputpart1.txt");
    Part1 part1;
    std::cout << part1.solve(input1) << std::endl;
    input1.close();
    input1.open("inputpart1.txt");
    Part2 part2;
    std::cout << part2.solve(input1) << std::endl;
    input1.close();
}
