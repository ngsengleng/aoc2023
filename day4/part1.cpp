#include "parts.h"
#include "base.cpp"

class Part1: public Base {
    const std::string DIVIDER = "|";
public:
    int solve(std::fstream& f) {
        int sum = 0;
        if (!f.is_open()) {
            return sum;
        }
        while (f) {
            int power = -1;
            std::string s;
            std::getline(f, s);
            std::vector<std::string> numbers = split(s, ":");
            std::vector<std::string> tokens = split(numbers[1], " ");

            size_t i = 0;
            std::set<std::string> winningNumbers;
            while (i < tokens.size()) {
                std::string winningNumber = tokens[i];
                if (winningNumber == DIVIDER) {
                    i++;
                    break;
                }
                if (!winningNumber.empty()) {
                    winningNumbers.insert(winningNumber);
                }
                i++;
            }
            while (i < tokens.size()) {
                std::string number = tokens[i];
                if (winningNumbers.find(number) != winningNumbers.end()) {
                    power++;
                }
                i++;
            }
            sum += pow(2, power);
        }
        return sum;
    }
};