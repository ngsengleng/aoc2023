#include "parts.h"
#include "base.cpp"

class Part1: public Base {
public:
    int solve(std::fstream& f) {
        if (!f.is_open()) {
            return 0;
        }
        std::unordered_map<std::string, int> maxColors;
        maxColors["red"] = 12;
        maxColors["green"] = 13;
        maxColors["blue"] = 14;
        int sum = 0;

        while (f) {
            std::string s;
            std::getline(f, s);
            if (s.empty()) {
                break;
            }
            std::vector<std::string> tokens = split(s, ":");
            int gameId = std::stoi(split(tokens[0], " ")[1]);
            std::vector<std::string> selections = split(tokens[1], ";");
            bool valid = true;
            for (const std::string& selection : selections) {
                std::vector<std::string> balls = split(selection, ",");
                for (const std::string& ball : balls) {
                    std::vector<std::string> numberColorPair = split(ball, " ");
                    numberColorPair.erase(numberColorPair.begin());
                    if (maxColors[numberColorPair[1]] < std::stoi(numberColorPair[0])) {
                        valid = false;
                        break;
                    }
                }
                if (!valid) {
                    break;
                }
            }
            if (!valid) {
                continue;
            }

            sum += gameId;
        }
        return sum;
    }
};