#include "solver.h"

void Solver::solve(std::fstream &f, bool isPartOne) {
    if (!f.is_open()) {
        std::cerr << "file not open" << std::endl;
        return;
    }
    std::vector<Hand> cardHands;
    while (f) {
        std::string s;
        std::getline(f, s);
        if (s.empty()) {
            break;
        }
        Hand hand = Hand(s, isPartOne);

        if (s.find('J') != std::string::npos) {
            cardHands.push_back(hand);
        } else {
            cardHands.push_back(hand);
        }
    }
    std::sort(cardHands.begin(), cardHands.end(), [](auto& lhs, auto& rhs) {
        return lhs.compare(lhs, rhs);
    });
    long total = 0L;
    for (size_t i = 0; i < cardHands.size(); i++) {
        total += cardHands[i].getValue() * ((int) i + 1);
    }
    if (isPartOne) {
        std::cout << "answer for part 1: ";
    } else {
        std::cout << "answer for part 2: ";
    }
    std::cout << total << std::endl;
}
