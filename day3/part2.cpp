#include "parts.h"

class Part2 {
    const std::string NO_RESULT = "nores";
private:
    std::string findGearCoords(size_t xIdx, size_t yIdx, std::vector<std::string>& map) {
        size_t rowSize = map[0].size();
        size_t colSize = map.size();
        for (std::pair<int, int> dir : directions) {
            int newX = dir.first + xIdx;
            int newY = dir.second + yIdx;
            if (newX < 0 || newX == rowSize) {
                continue;
            }
            if (newY < 0 || newY == colSize) {
                continue;
            }
            char c = map[newY][newX];
            if (c == '*') {
                return std::to_string(newX) + "," + std::to_string(newY);
            }
        }
        return NO_RESULT;
    }
public:
    int solve(std::fstream& f) {
        int sum = 0;
        if (!f.is_open()) {
            return sum;
        }
        std::vector<std::string> map;
        while (f) {
            std::string s;
            std::getline(f, s);
            if (s.empty()) {
                break;
            }
            map.push_back(s);
        }

        std::unordered_map<std::string, std::vector<int>> validGears;
        for (size_t r = 0; r < map.size(); r++) {
            std::string row = map[r];
            size_t c = 0;
            std::string coords;
            bool isGear = false;
            while (c < row.size()) {
                std::string num;
                while (c < row.size() && isdigit(row[c])) {
                    num += row[c];
                    if (!isGear) {
                        coords = findGearCoords(c, r, map);
                        if (coords != NO_RESULT) {
                            isGear = true;
                        }
                    }
                    c++;
                }
                if (isGear) {
                    validGears[coords].push_back(std::stoi(num));
                    isGear = false;
                }
                if (!isdigit(row[c])) {
                    c++;
                }
            }
        }
        for (auto& keyValues : validGears) {
            std::vector<int> numbers = keyValues.second;
            if (numbers.size() != 2) {
                continue;
            }
            sum += numbers[0] * numbers[1];
        }
        return sum;
    }
};