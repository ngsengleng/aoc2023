#include "solver.h"

class Solver {

enum DataTypes {
    ETime,
    EDistance,
};

static std::vector<std::string> split(const std::string& s, const std::string& delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

static long findWays(long givenTime, long recordDistance) {
    int a = -1;
    long b = givenTime;
    long c = -recordDistance;
    long discriminant = b*b - 4*a*c;
    if (discriminant > 0) {
        long x1 = std::floor(((double) -b + sqrt(discriminant)) / (2*a));
        long x2 = std::floor(((double) -b - sqrt(discriminant)) / (2*a));
        long distance = a * (long) pow(x1, 2) + b * x1 + c;
        if (distance <= 0) {
            x1++;
        }
        distance = a * (long) pow(x2, 2) + b * x2 + c;
        if (distance == 0) {
            x2--;
        }
        return x2 - x1 + 1;
    } else if (discriminant == 0) {
        return 1;
    }
    return 0;
}

public:
    void solvePart1(std::fstream& f) {
        if (!f.is_open()) {
            std::cerr << "file not open" << std::endl;
            return;
        }
        std::vector<std::vector<int>> timeDistanceRecords;
        std::vector<std::vector<int>> numberSize;
        int count = 0;
        while (f) {
            std::string s;
            std::getline(f, s);
            if (s.empty()) {
                break;
            }
            timeDistanceRecords.emplace_back();
            numberSize.emplace_back();
            std::vector<std::string> tokens = split(s, " ");
            for (std::string& token : tokens) {
                if (isdigit(token[0])) {
                    timeDistanceRecords[count].push_back(std::stoi(token));
                    numberSize[count].push_back((int) token.size());
                }
            }
            count++;
        }
        size_t recordCount = timeDistanceRecords[0].size();
        long res = 1L;
        for (size_t i = 0; i < recordCount; i++) {
            int givenTime = timeDistanceRecords[ETime][i];
            int recordDistance = timeDistanceRecords[EDistance][i];

            long ways = findWays(givenTime, recordDistance);
            res *= ways;
        }
        std::cout << "answer for part 1: ";
        std::cout << res << std::endl;

        long newTime = 0;
        long newDistance = 0;
        int timeMultiplier = 0;
        int distanceMultiplier = 0;
        int POWER_CONST = 10;
        for (size_t i = recordCount - 1; i != SIZE_T_MAX; i--) {
            newTime += (long) timeDistanceRecords[ETime][i] * (long) pow(POWER_CONST, timeMultiplier);
            timeMultiplier += numberSize[ETime][i];
            newDistance += (long) timeDistanceRecords[EDistance][i] * (long) pow(POWER_CONST, distanceMultiplier);
            distanceMultiplier += numberSize[EDistance][i];
        }
        long ways = findWays(newTime, newDistance);
        std::cout << "answer for part 2: ";
        std::cout << ways << std::endl;

    }
};