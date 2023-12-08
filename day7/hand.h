#ifndef DAY7_HAND_H
#define DAY7_HAND_H

#include <string>
#include <unordered_map>
#include "utils.h"

class Hand {
    enum HandTypes {
        HIGH_CARD,
        ONE_PAIR,
        TWO_PAIR,
        THREE_KIND,
        FULL_HOUSE,
        FOUR_KIND,
        FIVE_KIND
    };

    HandTypes type;
    std::string cardHand;
    int value;
    static const int HAND_SIZE = 5;
    bool isPartOne;

    int convertCardValue(const char& c);
public:
    Hand(const std::string& s, bool isPartOne);
    HandTypes getType() const;
    int getValue() const;
    char getCard(int pos) const;
    bool compare(const Hand& lhs, const Hand& rhs);
};

#endif //DAY7_HAND_H
