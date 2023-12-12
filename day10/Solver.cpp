#include "Solver.h"

std::vector<int> Solver::split(const std::string& s, const std::string& delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<int> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (std::stoi(token));
    }

    res.push_back (std::stoi(s.substr (pos_start)));
    return res;
}

Solver::DirectionType Solver::intToDirection(const size_t& i) {
    if (i == 0) return Left;
    if (i == 1) return Up;
    if (i == 2) return Right;
    if (i == 3) return Down;
    if (i > 3) {
        std::cerr << "possible error in direction hash" << std::endl;
    }
    return Invalid;
}

std::string Solver::coordinateToString(const Coordinate& c) {
    return std::to_string(c.first) + ',' + std::to_string(c.second);
}

Solver::Coordinate Solver::StringToCoord(const std::string& s) {
    std::vector<int> numbers = split(s, ",");
    return std::make_pair(numbers[0], numbers[1]);
}

bool Solver::withinBoundary(const int& x, const size_t& boundary) {
    return x >= 0 && x < boundary;
}

bool Solver::isConsecutivePipe(const char &leftPipe, const char &rightPipe) {
    std::unordered_set<char> rightFacingPipes{'F', 'L', '-'};
    std::unordered_set<char> leftFacingPipes{'J', '7', '-'};
    if (rightFacingPipes.find(leftPipe) != rightFacingPipes.end()) {
        return leftFacingPipes.find(rightPipe) != leftFacingPipes.end();
    }
}

bool Solver::isOppositeDirection(const char &leftPipe, const char &rightPipe) {
    return (leftPipe == 'L' && rightPipe == 'J')
        || (leftPipe == 'F' && rightPipe == '7')
        || (leftPipe == 'J' && rightPipe == 'L')
        || (leftPipe == 'J' && rightPipe == 'F')
        || (leftPipe == 'J' && rightPipe == '|')
        || (leftPipe == '7' && rightPipe == 'F')
        || (leftPipe == '7' && rightPipe == 'L')
        || (leftPipe == '7' && rightPipe == '|')
        || (leftPipe == '|' && rightPipe == '|')
        || (leftPipe == '|' && rightPipe == 'F')
        || (leftPipe == '|' && rightPipe == 'L');
}

void Solver::solve(std::fstream &f) {
    if (!f.is_open()) {
        std::cerr << "file not open" << std::endl;
        return;
    }

    std::vector<std::string> pipes;
    int counter = 0;
    Coordinate startCoord;
    while (f) {
        std::string s;
        std::getline(f, s);
        if (s.empty()) {
            continue;
        }
        pipes.push_back(s);
        if (s.find('S') != std::string::npos) {
            startCoord = std::make_pair(counter, s.find('S'));
        }
        counter++;
    }

    // a lot of definitions
    size_t rows = pipes.size();
    size_t columns = pipes[0].size();
    std::unordered_map<char, std::unordered_map<int, PipeSet>> validPipesMapping;
    std::vector<char> pipeTypes = {'F', 'L', 'J', '7', '|', '-'};
    std::vector<Direction> directions = {
            std::make_pair(0, -1), // left
            std::make_pair(-1, 0), // up
            std::make_pair(0, 1), // right
            std::make_pair(1, 0), // down
    };
    PipeSet rightPipes{pipeTypes[2], pipeTypes[3], pipeTypes[5]};
    PipeSet leftPipes{pipeTypes[0], pipeTypes[1], pipeTypes[5]};
    PipeSet topPipes{pipeTypes[0], pipeTypes[3], pipeTypes[4]};
    PipeSet bottomPipes{pipeTypes[1], pipeTypes[2], pipeTypes[4]};

    validPipesMapping[pipeTypes[0]] = {
            {Right, rightPipes},
            {Down, bottomPipes}
    };
    validPipesMapping[pipeTypes[1]] = {
            {Up, topPipes},
            {Right, rightPipes}
    };
    validPipesMapping[pipeTypes[2]] = {
            {Left, leftPipes},
            {Up, topPipes}
    };
    validPipesMapping[pipeTypes[3]] = {
            {Left, leftPipes},
            {Down, bottomPipes}
    };
    validPipesMapping[pipeTypes[4]] = {
            {Up, topPipes},
            {Down, bottomPipes}
    };
    validPipesMapping[pipeTypes[5]] = {
            {Left, leftPipes},
            {Right, rightPipes}
    };

    std::deque<Coordinate> pipeQueue;
    std::unordered_set<std::string> visitedPipes;
    visitedPipes.insert(coordinateToString(startCoord));
    std::string startPipeType;
    for (size_t i = 0; i < directions.size(); i++) {
        Direction d = directions[i];
        int newR = startCoord.first + d.first;
        if (!withinBoundary(newR, rows)) {
            continue;
        }
        int newC = startCoord.second + d.second;
        if (!withinBoundary(newC, columns)) {
            continue;
        }
        Coordinate newCoord = std::make_pair(newR, newC);
        char pipe = pipes[newR][newC];
        DirectionType dir = intToDirection(i);
        switch (dir) {
            case (Left):
                if (leftPipes.find(pipe) != leftPipes.end()) {
                    pipeQueue.push_back(newCoord);
                    visitedPipes.insert(coordinateToString(newCoord));
                    startPipeType += "left";
                }
                break;
            case (Right):
                if (rightPipes.find(pipe) != rightPipes.end()) {
                    pipeQueue.push_back(newCoord);
                    visitedPipes.insert(coordinateToString(newCoord));
                    startPipeType += "right";
                }
                break;
            case (Up):
                if (topPipes.find(pipe) != topPipes.end()) {
                    pipeQueue.push_back(newCoord);
                    visitedPipes.insert(coordinateToString(newCoord));
                    startPipeType += "up";
                }
                break;
            case (Down):
                if (bottomPipes.find(pipe) != bottomPipes.end()) {
                    pipeQueue.push_back(newCoord);
                    visitedPipes.insert(coordinateToString(newCoord));
                    startPipeType += "down";
                }
                break;
            case Invalid:
                break;
        }
    }
    // leftuprightdown
    if (startPipeType == "leftright") {
        pipes[startCoord.first][startCoord.second] = '-';
    } else if (startPipeType == "leftup") {
        pipes[startCoord.first][startCoord.second] = 'J';
    } else if (startPipeType == "leftdown") {
        pipes[startCoord.first][startCoord.second] = '7';
    } else if (startPipeType == "updown") {
        pipes[startCoord.first][startCoord.second] = '|';
    } else if (startPipeType == "upright") {
        pipes[startCoord.first][startCoord.second] = 'L';
    } else if (startPipeType == "rightdown") {
        pipes[startCoord.first][startCoord.second] = 'F';
    }

    std::unordered_map<int, std::vector<Coordinate>> pipeLocations;
    long distance = 0;
    while (!pipeQueue.empty()) {
        for (size_t i = 0; i < pipeQueue.size(); i++) {
            Coordinate curr = pipeQueue.front();
            if (pipeLocations.find(curr.first) == pipeLocations.end()) {
                pipeLocations[curr.first] = {};
            }
            pipeLocations[curr.first].push_back(curr);
            char currPipe = pipes[curr.first][curr.second];
            pipeQueue.pop_front();
            for (size_t j = 0; j < directions.size(); j++) {
                DirectionType dir = intToDirection(j);
                std::unordered_map<int, PipeSet> validPipes = validPipesMapping[currPipe];
                if (validPipes.find(dir) == validPipes.end()) {
                    continue;
                }
                Direction d = directions[j];
                int newR = curr.first + d.first;
                if (!withinBoundary(newR, rows)) {
                    continue;
                }
                int newC = curr.second + d.second;
                if (!withinBoundary(newC, columns)) {
                    continue;
                }
                char newPipe = pipes[newR][newC];
                Coordinate newCoord = std::make_pair(newR, newC);
                std::string coordString = coordinateToString(newCoord);
                if (visitedPipes.find(coordString) != visitedPipes.end()) {
                    continue;
                }
                visitedPipes.insert(coordString);
                if (validPipes[dir].find(newPipe) != validPipes[dir].end()) {
                    pipeQueue.push_back(newCoord);
                }
            }
        }
        distance++;
    }
    std::cout << "answer for part 1: ";
    std::cout << distance << std::endl;

    // use Point in Polygon for part 2?
    pipeLocations[startCoord.first].push_back(startCoord);
    long res = 0L;

    for (int i = 0; i < rows; i++) {
        if (pipeLocations.find(i) == pipeLocations.end()) {
            continue;
        }
        std::vector<Coordinate> polygonPoints = pipeLocations[i];
        std::sort(polygonPoints.begin(), polygonPoints.end());
        Coordinate prevPoint = polygonPoints[0];
        Coordinate prevDirChangePoint = polygonPoints[0];
        bool isUp = false;
        int windCount = 1;
        for (int j = 1; j < polygonPoints.size(); j++) {
            Coordinate point = polygonPoints[j];
            char leftPipe = pipes[prevPoint.first][prevPoint.second];
            char rightPipe = pipes[point.first][point.second];
            char prevDirChangePointPipe = pipes[prevDirChangePoint.first][prevDirChangePoint.second];

            if (rightPipe == '-') {
                prevPoint = point;
                continue;
            }
            if (!isConsecutivePipe(leftPipe, rightPipe)) {
                if (windCount != 0) {
                    res += point.second - prevPoint.second - 1;
                }
            }
            if (isOppositeDirection(prevDirChangePointPipe, rightPipe)) {
                isUp = !isUp;
                if (isUp) {
                    windCount--;
                } else {
                    windCount++;
                }
            }
            prevDirChangePoint = point;
            prevPoint = point;
        }
    }
    std::cout << "answer for part 2: ";
    std::cout << res << std::endl;
}
