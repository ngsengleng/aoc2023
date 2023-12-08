#include "hand.h"

Hand::Hand(const std::string &s, bool isPartOne) {
    std::vector<std::string> tokens = Utils::split(s, " ");
    this -> cardHand = tokens[0];
    this -> value = std::stoi(tokens[1]);
    this -> isPartOne = isPartOne;

    std::unordered_map<char, int> cardCount;
    for (char c : tokens[0]) {
        if (cardCount.find(c) == cardCount.end()) {
            cardCount[c] = 1;
        } else {
            cardCount[c]++;
        }
    }

    size_t uniques = cardCount.size();
    int jokerCount = cardCount['J'] * !isPartOne;
    if (uniques == 5) {
        type = HIGH_CARD;
        if (jokerCount == 1) {
            type = ONE_PAIR;
        }
    } else if (uniques == 4) {
        type = ONE_PAIR;
        if (jokerCount == 1 || jokerCount == 2) {
            type = THREE_KIND;
        }
    } else if (uniques == 3) {
        for (auto& kv : cardCount) {
            if (kv.second == 3) {
                type = THREE_KIND;
            } else if (kv.second == 2) {
                type = TWO_PAIR;
            }
        }
        if (type == TWO_PAIR) {
            if (jokerCount == 2) {
                type = FOUR_KIND;
            }
            if (jokerCount == 1) {
                type = FULL_HOUSE;
            }
        } else {
            if (jokerCount == 3 || jokerCount == 1) {
                type = FOUR_KIND;
            }
        }
    } else if (uniques == 2) {
        for (auto& kv : cardCount) {
            if (kv.second == 4 || kv.second == 1) {
                type = FOUR_KIND;
            } else if (kv.second == 2 || kv.second == 3) {
                type = FULL_HOUSE;
            }
        }
        if (jokerCount != 0) {
            type = FIVE_KIND;
        }
    } else {
        type = FIVE_KIND;
    }
}

int Hand::convertCardValue(const char& c) {
    std::unordered_map<char, int> cardValues;
    cardValues['A'] = 14;
    cardValues['K'] = 13;
    cardValues['Q'] = 12;
    if (this -> isPartOne) {
        cardValues['J'] = 11;
    } else {
        cardValues['J'] = 0;
    }
    cardValues['T'] = 10;
    if (isdigit(c)) {
        return c - '0';
    } else {
        return cardValues[c];
    }
}

bool Hand::compare(const Hand& lhs, const Hand& rhs) {

    if (lhs.getType() == rhs.getType()) {
        for (int i = 0; i < Hand::HAND_SIZE; i++) {
            char cardOne = lhs.getCard(i);
            char cardTwo = rhs.getCard(i);
            int cardValueOne = this -> convertCardValue(cardOne);
            int cardValueTwo = this -> convertCardValue(cardTwo);
            if (cardValueOne == cardValueTwo) {
                continue;
            }
            return cardValueOne < cardValueTwo;
        }
    }

    return lhs.getType() < rhs.getType();
};

Hand::HandTypes Hand::getType() const {
    return type;
}

int Hand::getValue() const {
    return value;
}

char Hand::getCard(int pos) const {
    return cardHand[pos];
}
