#ifndef DAY10_SOLVER_H
#define DAY10_SOLVER_H

#include <fstream>
#include <iostream>
#include <string>
#include <deque>
#include <unordered_map>
#include <unordered_set>

class Solver {
typedef std::pair<int, int> Direction;
typedef std::pair<int, int> Coordinate;
typedef std::unordered_set<char> PipeSet;
enum DirectionType {
    Left,
    Up,
    Right,
    Down,
    Invalid
};

static DirectionType intToDirection(const size_t& i);
static std::string coordinateToString(const Coordinate& c);
static Coordinate StringToCoord(const std::string& s);
static std::vector<int> split(const std::string& s, const std::string& delimiter);
static bool withinBoundary(const int& x, const size_t& boundary);
static bool isConsecutivePipe(const char& leftPipe, const char& rightPipe);
static bool isOppositeDirection(const char& leftPipe, const char& rightPipe);
public:
    static void solve(std::fstream& f);
};


#endif //DAY10_SOLVER_H
