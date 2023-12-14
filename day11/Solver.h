#ifndef DAY11_SOLVER_H
#define DAY11_SOLVER_H

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

class Solver {
typedef std::pair<long, long> Coordinate;
static const char GALAXY = '#';
static const char SPACE = '.';
public:
    static void solve(std::fstream& f);
};


#endif //DAY11_SOLVER_H
