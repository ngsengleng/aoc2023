#include "parts.h"

class Part2 {
    private:
        bool hasKey(const std::unordered_map<std::string, std::string>& hashmap, std::string s) {
            return hashmap.find(s) != hashmap.end();
        }

        std::string getNumber(std::string& s,
                              int idx,
                              std::unordered_map<std::string, std::string>& hashmap) {
            std::string substr = s.substr(idx, 3); // one, two, six
            if (hasKey(hashmap, substr)) {
                return hashmap[substr];
            }
            substr = s.substr(idx, 4); // four, five, nine
            if (hasKey(hashmap, substr)) {
                return hashmap[substr];
            }
            substr = s.substr(idx, 5); // three, seven, eight
            if (hasKey(hashmap, substr)) {
                return hashmap[substr];
            }
            return "";
        }

    public:
        int solve(std::fstream &f) {
            int sum = 0;
            if (!f.is_open()) {
                return sum;
            }

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
                        std::string digit = getNumber(s, i, numbers);
                        if (digit.empty()) {
                            continue;
                        }
                        number += digit;
                        break;
                    }
                }

                for (size_t i = s.size() - 1; i != SIZE_T_MAX; i--) {
                    char c = s[i];
                    if (isdigit(c)) {
                        number += c;
                        break;
                    }
                    if (firstLetters.find(c) != firstLetters.end()) {
                        std::string digit = getNumber(s, i, numbers);
                        if (digit.empty()) {
                            continue;
                        }
                        number += digit;
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