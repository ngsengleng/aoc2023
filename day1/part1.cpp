#include "parts.h"

class Part1 {
    public:
        int solve(std::fstream &f) {
            int sum = 0;
            if (!f.is_open()) {
                return sum;
            }
            while (f) {
                std::string s;
                std::getline(f, s);
                std::string number;
                for (char c : s) {
                    if (isdigit(c)) {
                        number += c;
                        break;
                    }
                }
                for (size_t i = s.size() - 1; i != SIZE_T_MAX; i--) {
                    if (isdigit(s[i])) {
                        number += s[i];
                        break;
                    }
                }
                if (number.empty()) {
                    continue;
                }
                sum += std::stoi(number);
            }
            return sum;
        }
};