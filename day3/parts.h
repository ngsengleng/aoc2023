#ifndef DAY3_PARTS_H
#define DAY3_PARTS_H

#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>

const std::pair<int, int> directions[8] = {
        std::make_pair(1, 0),
        std::make_pair(1, 1),
        std::make_pair(0, 1),
        std::make_pair(-1, 1),
        std::make_pair(-1, 0),
        std::make_pair(-1, -1),
        std::make_pair(0, -1),
        std::make_pair(1, -1),
};

#endif //DAY3_PARTS_H
