#include "Solver.h"

unsigned long traverseNodes(std::unordered_map<std::string, Node> nodeMap,
        const std::string& startingNode,
        const std::string& instructions) {
    std::string currNode = startingNode;
    unsigned long instructionCount = instructions.size();
    unsigned long currentCount = 0L;
    while (currNode[2] != 'Z') {
        char currentInstruction = instructions[currentCount % instructionCount];
        if (currentInstruction == 'L') {
            currNode = nodeMap[currNode].first;
        } else {
            currNode = nodeMap[currNode].second;
        }
        currentCount++;
    }
    return currentCount;
}

unsigned long gcd(unsigned long a, unsigned long b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

void Solver::solve(std::fstream &f) {
    if (!f.is_open()) {
        std::cerr << "file not open" << std::endl;
        return;
    }

    std::unordered_map<std::string, Node> nodeMap;
    std::string instructions;
    bool hasInstructions = false;
    while (f) {
        std::string s;
        std::getline(f, s);
        if (s.empty()) {
            continue;
        }
        if (!hasInstructions) {
            instructions = s;
            hasInstructions = true;
            continue;
        }

        std::regex word_regex("([A-Z])\\w+");
        auto words_begin = std::sregex_iterator(s.begin(), s.end(), word_regex);
        auto words_end = std::sregex_iterator();
        std::vector<std::string> tokens;
        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            const std::smatch& match = *i;
            std::string matchString = match.str();
            tokens.push_back(matchString);
        }
        nodeMap[tokens[0]] = std::make_pair(tokens[1], tokens[2]);
    }

    std::string currNode = "AAA";
    unsigned long instructionCount = instructions.size();
    unsigned long currentCount = 0L;
    while (currNode != "ZZZ") {
        char currentInstruction = instructions[currentCount % instructionCount];
        if (currentInstruction == 'L') {
            currNode = nodeMap[currNode].first;
        } else {
            currNode = nodeMap[currNode].second;
        }
        currentCount++;
    }
    std::cout << "answer for part 1: ";
    std::cout << currentCount << std::endl;

    std::vector<std::string> startingNodes;
    for (auto& kv : nodeMap) {
        if (kv.first[2] == 'A') {
            startingNodes.push_back(kv.first);
        }
    }
    unsigned long lowestCommonCount = 1;
    for (const std::string& startingNode : startingNodes) {
        unsigned long count = traverseNodes(nodeMap, startingNode, instructions);
        lowestCommonCount = (count * lowestCommonCount) / gcd(count, lowestCommonCount);
    }
    std::cout << "answer for part 2: ";
    std::cout << lowestCommonCount << std::endl;

}
