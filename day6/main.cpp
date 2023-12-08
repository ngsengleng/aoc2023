#include "solver.cpp"

int main() {
    Solver solver;
    std::fstream f;
    std::string testFile = "../test6.txt";
    f.open(testFile);
    solver.solvePart1(f);
    f.close();
    std::string inputFile = "../input6.txt";
    f.open(inputFile);
    solver.solvePart1(f);
    f.close();
}
