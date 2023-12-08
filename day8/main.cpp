#include "Solver.h"

int main() {
    std::fstream f;
    std::string testFile = "../test8.txt";
    std::string testFile2 = "../test8two.txt";
    std::string inputFile = "../input8.txt";
//    f.open(testFile);
//    Solver::solve(f);
//    f.close();
//    f.open(testFile2);
//    Solver::solve(f);
//    f.close();
    f.open(inputFile);
    Solver::solve(f);
    f.close();
}
