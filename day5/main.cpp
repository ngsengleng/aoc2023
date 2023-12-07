#include <iostream>
#include "solver.cpp"

int main() {
    std::fstream f;
    Solver solver;
    std::string testFile = "../test5.txt";
    f.open(testFile);
    std::cout << "running " + testFile << std::endl;
    solver.solve(f);
    f.close();
    std::string inputFile = "../input5.txt";
    f.open(inputFile);
    std::cout << "running " + inputFile << std::endl;
    solver.solve(f);
    f.close();
}
