#ifndef DAY9_SOLVER_H
#define DAY9_SOLVER_H

#include <string>
#include <queue>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <numeric>

class Solver {
static std::vector<int> split(const std::string& s, const std::string& delimiter);
public:
    static void solve(std::fstream& f);
};

#endif //DAY9_SOLVER_H
