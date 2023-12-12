#include "Solver.h"

int main() {
    std::fstream f;
    std::string simpleTestFile = "../testSimple.txt";
    std::string complexTestFile = "../testComplex.txt";
    std::string inputFile = "../input10.txt";
    f.open(simpleTestFile);
    Solver::solve(f);
    f.close();
    f.open(complexTestFile);
    Solver::solve(f);
    f.close();
    std::string polygonTestFile = "../testPolygon";
    for (int i = 1; i < 4; i++) {
        std::string s = polygonTestFile + std::to_string(i) + ".txt";
        f.open(s);
        Solver::solve(f);
        f.close();
    }
    f.open(inputFile);
    Solver::solve(f);
    f.close();
}
