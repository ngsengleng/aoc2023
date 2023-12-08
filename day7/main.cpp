#include "solver.h"

int main() {
    std::fstream f;
    std::string testFile = "../test7.txt";
    f.open(testFile);
    Solver::solve(f, true);
    f.close();
    std::string inputFile = "../input7.txt";
    f.open(inputFile);
    Solver::solve(f, true);
    f.close();
    f.open(testFile);
    Solver::solve(f, false);
    f.close();
    f.open(inputFile);
    Solver::solve(f, false);
    f.close();
}
