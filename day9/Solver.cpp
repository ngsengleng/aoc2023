#include "Solver.h"

std::vector<int> Solver::split(const std::string& s, const std::string& delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<int> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (std::stoi(token));
    }

    res.push_back (std::stoi(s.substr (pos_start)));
    return res;
}

void Solver::solve(std::fstream& f) {
    if (!f.is_open()) {
        std::cerr << "file not open" << std::endl;
        return;
    }

    long part1 = 0L;
    long part2 = 0L;
    while (f) {
        std::string s;
        std::getline(f, s);
        if (s.empty()) {
            continue;
        }

        std::vector<int> tokens = Solver::split(s, " ");
        std::deque<int> queue;
        std::vector<int> lastNumbers;
        std::vector<int> firstNumbers;
        for (const int& token : tokens) {
            queue.push_back(token);
        }

        while (!queue.empty()) {
            int prevNumber = INT_MAX;
            size_t iterations = queue.size();
            lastNumbers.push_back(queue.back());
            firstNumbers.push_back(queue.front());

            for (size_t i = 0; i < iterations; i++) {
                int currNumber = queue.front();
                queue.pop_front();
                if (prevNumber == INT_MAX) {
                    prevNumber = currNumber;
                    continue;
                }
                queue.push_back(currNumber - prevNumber);
                prevNumber = currNumber;
            }
            if (std::all_of(queue.begin(), queue.end(), [](auto& a){return a==0;})) {
                break;
            }
        }
        part1 += std::accumulate(lastNumbers.begin(), lastNumbers.end(), 0);

        long res = 0;
        for (size_t i = firstNumbers.size() - 1; i != SIZE_T_MAX; i--) {
            res = firstNumbers[i] - res;
        }
        part2 += res;
    }
    std::cout << "answer for part 1: ";
    std::cout << part1 << std::endl;
    std::cout << "answer for part 2: ";
    std::cout << part2 << std::endl;
}
