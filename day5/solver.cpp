#include <iostream>
#include <thread>
#include "base.cpp"

class Solver: public Base {
private:
    static std::vector<RangePair> processRanges(const std::vector<RangePair>& ranges,
                                                     const std::vector<SourceDestMapper>& mappers) {
        std::vector<RangePair> res;
        for (auto& range : ranges) {
            std::vector<RangePair> newRanges = mapNewRanges(range, mappers);
            res.insert(res.end(), newRanges.begin(), newRanges.end());
        }
        return res;
    }

    static long getLowestLocation(const std::vector<RangePair>& locationRanges) {
        long minLocation = LONG_MAX;
        for (auto& range : locationRanges) {
            minLocation = std::min(minLocation, range.first);
        }
        return minLocation;
    }
public:
    void solve(std::fstream& f) {
        long minLocation = LONG_MAX;
        if (!f.is_open()) {
            return;
        }
        // in hindsight should have kept these as just a vector of vectors of mappers
        std::vector<long> seeds;
        std::vector<SourceDestMapper> seedSoilMaps;
        std::vector<SourceDestMapper> soilFertilizerMaps;
        std::vector<SourceDestMapper> fertilizerWaterMaps;
        std::vector<SourceDestMapper> waterLightMaps;
        std::vector<SourceDestMapper> lightTempMaps;
        std::vector<SourceDestMapper> tempHumidityMaps;
        std::vector<SourceDestMapper> humidityLocationMaps;

        Flags flag;
        while (f) {
            std::string s;
            std::getline(f, s);
            if (s.empty()) {
                continue;
            }
            // get seeds
            std::vector<std::string> tokens;
            if (s.find(SEED_FLAG) != std::string::npos) {
                tokens = split(s, ":");
                std::vector<std::string> seedTokens = split(tokens[1], " ");
                for (std::string& token : seedTokens) {
                    if (token.empty()) {
                        continue;
                    }
                    seeds.push_back(std::stol(token));
                }
                continue;
            }

            tokens = split(s, " ");
            // checks if its a map header or a mapping directive
            if (!std::isdigit(tokens[0][0])) {
                flag = flagHash(tokens[0]);
                continue;
            }
            // generate mappers for each category
            SourceDestMapper mapper = generateMapper(s);
            switch (flag) {
                case SEED_SOIL_FLAG:
                    seedSoilMaps.push_back(mapper);
                    break;
                case SOIL_FERTILIZER_FLAG:
                    soilFertilizerMaps.push_back(mapper);
                    break;
                case FERTILIZER_WATER_FLAG:
                    fertilizerWaterMaps.push_back(mapper);
                    break;
                case WATER_LIGHT_FLAG:
                    waterLightMaps.push_back(mapper);
                    break;
                case LIGHT_TEMP_FLAG:
                    lightTempMaps.push_back(mapper);
                    break;
                case TEMP_HUMIDITY_FLAG:
                    tempHumidityMaps.push_back(mapper);
                    break;
                case HUMIDITY_LOCATION_FLAG:
                    humidityLocationMaps.push_back(mapper);
                    break;
                case INVALID_FLAG:
                    std::cerr << "something went wrong" << std::endl;
                    break;
            }
        }

        // i THINK this runs them concurrently so benefits are dubious
        std::thread firstSort(sortMappers, std::ref(seedSoilMaps));
        std::thread secondSort(sortMappers, std::ref(fertilizerWaterMaps));
        std::thread thirdSort(sortMappers, std::ref(waterLightMaps));
        std::thread fourthSort(sortMappers, std::ref(lightTempMaps));
        std::thread fifthSort(sortMappers, std::ref(tempHumidityMaps));
        std::thread sixthSort(sortMappers, std::ref(humidityLocationMaps));
        std::thread seventhSort(sortMappers, std::ref(soilFertilizerMaps));
        firstSort.join();
        secondSort.join();
        thirdSort.join();
        fourthSort.join();
        fifthSort.join();
        sixthSort.join();
        seventhSort.join();

        // part1
        for (long& seed : seeds) {
            long location;
            location = mapValue(seed, seedSoilMaps);
            location = mapValue(location, soilFertilizerMaps);
            location = mapValue(location, fertilizerWaterMaps);
            location = mapValue(location, waterLightMaps);
            location = mapValue(location, lightTempMaps);
            location = mapValue(location, tempHumidityMaps);
            location = mapValue(location, humidityLocationMaps);
            minLocation = std::min(minLocation, location);
        }
        std::cout << "answer for part 1 is: ";
        std::cout << minLocation << std::endl;

        // part2
        long secondMinLocation = LONG_MAX;
        for (size_t i = 0; i < seeds.size() - 1; i += 2) {
            long seed = seeds[i];
            long seedRange = seeds[i + 1];
            RangePair seedRanges = std::make_pair(seed, seed + seedRange - 1);
            std::vector<RangePair> soilRanges = mapNewRanges(seedRanges, seedSoilMaps);
            std::vector<RangePair> fertilizerRanges = processRanges(soilRanges, soilFertilizerMaps);
            std::vector<RangePair> waterRanges = processRanges(fertilizerRanges, fertilizerWaterMaps);
            std::vector<RangePair> lightRanges = processRanges(waterRanges, waterLightMaps);
            std::vector<RangePair> tempRanges = processRanges(lightRanges, lightTempMaps);
            std::vector<RangePair> humidityRanges = processRanges(tempRanges, tempHumidityMaps);
            std::vector<RangePair> locationRanges = processRanges(humidityRanges, humidityLocationMaps);
            secondMinLocation = std::min(getLowestLocation(locationRanges), secondMinLocation);
        }
        std::cout << "answer for part 2 is: ";
        std::cout << secondMinLocation << std::endl;
    }
};