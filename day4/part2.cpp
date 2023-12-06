#include "parts.h"
#include "base.cpp"

class Part2 : public Base {
    const std::string DIVIDER = "|";
public:
    int solve(std::fstream& f) {
        int sum = 0;
        if (!f.is_open()) {
            return sum;
        }
        std::unordered_map<int, int> duplicateCards;
        while (f) {
            std::string s;
            std::getline(f, s);
            if (s.empty()) {
                break;
            }
            std::vector<std::string> numbers = split(s, ":");

            std::vector<std::string> cardIdTokens = split(numbers[0], " ");
            int currCardNumber = std::stoi(cardIdTokens[cardIdTokens.size() - 1]);
            if (duplicateCards.find(currCardNumber) == duplicateCards.end()) {
                duplicateCards[currCardNumber] = 1;
            } else {
                duplicateCards[currCardNumber]++;
            }

            std::vector<std::string> numberTokens = split(numbers[1], " ");

            size_t i = 0;
            std::set<std::string> winningNumbers;
            while (i < numberTokens.size()) {
                std::string winningNumber = numberTokens[i];
                if (winningNumber == DIVIDER) {
                    i++;
                    break;
                }
                if (!winningNumber.empty()) {
                    winningNumbers.insert(winningNumber);
                }
                i++;
            }
            int currCardCount = duplicateCards[currCardNumber];
            while (i < numberTokens.size()) {
                std::string number = numberTokens[i];
                if (winningNumbers.find(number) != winningNumbers.end()) {
                    currCardNumber++;
                    if (duplicateCards.find(currCardNumber) == duplicateCards.end()) {
                        duplicateCards[currCardNumber] = currCardCount;
                    } else {
                        duplicateCards[currCardNumber] += currCardCount;
                    }
                }
                i++;
            }
        }
        for (auto& keyValue : duplicateCards) {
            sum += keyValue.second;
        }
        return sum;
    }
};