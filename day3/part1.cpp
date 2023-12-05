#include "parts.h"

class Part1 {
private:
    bool isPartNumber(size_t xIdx, size_t yIdx, const std::vector<std::string>& map) {
        size_t rowSize = map[0].size();
        size_t colSize = map.size();
        const std::pair<int, int> directions[8] = {
                std::make_pair(1, 0),
                std::make_pair(1, 1),
                std::make_pair(0, 1),
                std::make_pair(-1, 1),
                std::make_pair(-1, 0),
                std::make_pair(-1, -1),
                std::make_pair(0, -1),
                std::make_pair(1, -1),
        };
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
            if (!isdigit(c) && c != '.') {
                return true;
            }
        }
        return false;
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


        for (size_t r = 0; r < map.size(); r++) {
            std::string row = map[r];
            size_t c = 0;
            bool isValid = false;
            while (c < row.size()) {
                std::string num;
                while (c < row.size() && isdigit(row[c])) {
                    num += row[c];
                    if (!isValid && isPartNumber(c, r, map)) {
                        isValid = true;
                    }
                    c++;
                }
                if (isValid) {
//                    std::cout << map[r] << std::endl;
//                    std::cout << num << std::endl;
                    sum += std::stoi(num);
                    isValid = false;
                }
                if (!isdigit(row[c])) {
                    c++;
                }
            }
        }
        return sum;
    }
};