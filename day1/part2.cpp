#include "parts.h"

class Part2 {
    public:
        int solve(std::fstream &f) {
            int sum = 0;
            if (!f.is_open()) {
                return sum;
            }

//            std::unordered_map<std::string, std::string> numbers = {
//                    {"one", "1"},
//                    {"two", "2"},
//                    {"three", "3"},
//                    {"four", "4"},
//                    {"five", "5"},
//                    {"six", "6"},
//                    {"seven", "7"},
//                    {"eight", "8"},
//                    {"nine", "9"},
//            };
            std::unordered_map<std::string, std::string> numbers;
            numbers["one"] = "1";
            numbers["two"] = "2";
            numbers["three"] = "3";
            numbers["four"] = "4";
            numbers["five"] = "5";
            numbers["six"] = "6";
            numbers["seven"] = "7";
            numbers["eight"] = "8";
            numbers["nine"] = "9";

            std::set<char> firstLetters;
            std::set<char> lastLetters;
            for (auto &pair : numbers) {
                firstLetters.insert(pair.first.front());
                lastLetters.insert(pair.first.back());
            }

            while (f) {
                std::string s;
                std::getline(f, s);
                std::string number;
//                s = "grbhpnjrtvrbslnfgthree47vbpncxqfourfp";

                for (size_t i = 0; i < s.size(); i++) {
                    char c = s[i];
                    if (isdigit(c)) {
                        number += c;
                        break;
                    }
                    if (firstLetters.find(c) != firstLetters.end()) {
                        std::string substr = s.substr(i, 3); // one, two, six
                        if (numbers.find(substr) != numbers.end()) {
                            number += numbers[substr];
                            break;
                        }
                        substr = s.substr(i, 4); // four, five, nine
                        if (numbers.find(substr) != numbers.end()) {
                            number += numbers[substr];
                            break;
                        }
                        substr = s.substr(i, 5); // three, seven, eight
                        if (numbers.find(substr) != numbers.end()) {
                            number += numbers[substr];
                            break;
                        }
                    }
                }

                for (size_t i = s.size() - 1; i != SIZE_T_MAX; i--) {
                    char c = s[i];
                    if (isdigit(c)) {
                        number += c;
                        break;
                    }
                    if (firstLetters.find(c) != firstLetters.end()) {
                        std::string substr = s.substr(i, 3); // one, two, six
                        if (numbers.find(substr) != numbers.end()) {
                            number += numbers[substr];
                            break;
                        }
                        substr = s.substr(i, 4); // four, five, nine
                        if (numbers.find(substr) != numbers.end()) {
                            number += numbers[substr];
                            break;
                        }
                        substr = s.substr(i, 5); // three, seven, eight
                        if (numbers.find(substr) != numbers.end()) {
                            number += numbers[substr];
                            break;
                        }
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