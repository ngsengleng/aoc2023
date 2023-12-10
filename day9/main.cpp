#include "Solver.h"

int main() {
    std::fstream f;
    std::string testFile = "../test9.txt";
    std::string inputFile = "../input9.txt";
    f.open(testFile);
    Solver::solve(f);
    f.close();
    f.open(inputFile);
    Solver::solve(f);
    f.close();
}
