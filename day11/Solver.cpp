#include "Solver.h"

void Solver::solve(std::fstream &f) {
    if (!f.is_open()) {
        std::cerr << "file not open" << std::endl;
        return;
    }

    std::unordered_set<int> occupiedRows;
    std::unordered_set<int> occupiedColumns;
    int count = 0;
    std::vector<std::string> galaxyMap;
    while (f) {
        std::string s;
        std::getline(f, s);
        if (s.empty()) {
            continue;
        }
        if (s.find(GALAXY) != std::string::npos) {
            occupiedRows.insert(count);
        }
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == GALAXY) {
                occupiedColumns.insert(i);
            }
        }
        galaxyMap.push_back(s);
        count++;
    }
    long expansion = 1;
    std::vector<Coordinate> galaxies;
    long extraRows = 0;
    for (int r = 0; r < galaxyMap.size(); r++) {
        long extraColumns = 0;
        if (occupiedRows.find(r) == occupiedRows.end()) {
            extraRows += expansion;
        }
        for (int c = 0; c < galaxyMap[0].size(); c++) {
            if (occupiedColumns.find(c) == occupiedColumns.end()) {
                extraColumns += expansion;
            }
            if (galaxyMap[r][c] == GALAXY) {
                galaxies.emplace_back(r + extraRows, c + extraColumns);
            }
        }
    }

    long part1 = 0;
    for (size_t i = 0; i < galaxies.size(); i++) {
        Coordinate leftGalaxy = galaxies[i];
        for (size_t j = i; j < galaxies.size(); j++) {
            Coordinate rightGalaxy = galaxies[j];
            part1 += labs(leftGalaxy.first - rightGalaxy.first) + labs(leftGalaxy.second - rightGalaxy.second);
        }
    }
    std::cout << "answer for part 1: ";
    std::cout << part1 << std::endl;

    std::vector<Coordinate> expandedGalaxies;
    extraRows = 0;
    expansion = 999999;
    for (int r = 0; r < galaxyMap.size(); r++) {
        long extraColumns = 0;
        if (occupiedRows.find(r) == occupiedRows.end()) {
            extraRows += expansion;
        }
        for (int c = 0; c < galaxyMap[0].size(); c++) {
            if (occupiedColumns.find(c) == occupiedColumns.end()) {
                extraColumns += expansion;
            }
            if (galaxyMap[r][c] == GALAXY) {
                expandedGalaxies.emplace_back(r + extraRows, c + extraColumns);
            }
        }
    }
    long part2 = 0;
    for (size_t i = 0; i < expandedGalaxies.size(); i++) {
        Coordinate leftGalaxy = expandedGalaxies[i];
        for (size_t j = i; j < expandedGalaxies.size(); j++) {
            Coordinate rightGalaxy = expandedGalaxies[j];
            part2 += labs(leftGalaxy.first - rightGalaxy.first) + labs(leftGalaxy.second - rightGalaxy.second);
        }
    }
    std::cout << "answer for part 2: ";
    std::cout << part2 << std::endl;
}
