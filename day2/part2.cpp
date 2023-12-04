#include "parts.h"
#include "base.cpp"

class Part2 : public Base {
public:
    int solve(std::fstream& f) {
        if (!f.is_open()) {
            return 0;
        }
        int sum = 0;

        while (f) {
            std::string s;
            std::getline(f, s);
            if (s.empty()) {
                break;
            }
            std::vector<std::string> tokens = split(s, ":");
            std::vector<std::string> selections = split(tokens[1], ";");
            std::unordered_map<std::string, int> maxColors;
            maxColors["red"] = 0;
            maxColors["blue"] = 0;
            maxColors["green"] = 0;
            for (const std::string &selection: selections) {
                std::vector<std::string> balls = split(selection, ",");
                for (const std::string &ball: balls) {
                    std::vector<std::string> numberColorPair = split(ball, " ");
                    numberColorPair.erase(numberColorPair.begin());
                    int numberOfCubes = std::stoi(numberColorPair[0]);
                    if (maxColors[numberColorPair[1]] < numberOfCubes) {
                        maxColors[numberColorPair[1]] = numberOfCubes;
                    }
                }
            }
            int power = 1;
            for (auto &pair: maxColors) {
                power *= pair.second;
            }
            sum += power;
        }
        return sum;
    }
};