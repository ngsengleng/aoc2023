#include <cmath>
#include <iostream>
#include "sourceDestMapper.cpp"

class Base {
public:
    std::string SEED_FLAG = "seeds";
    enum Flags {
        SEED_SOIL_FLAG,
        SOIL_FERTILIZER_FLAG,
        FERTILIZER_WATER_FLAG,
        WATER_LIGHT_FLAG,
        LIGHT_TEMP_FLAG,
        TEMP_HUMIDITY_FLAG,
        HUMIDITY_LOCATION_FLAG,
        INVALID_FLAG,
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

    static Flags flagHash(const std::string& s) {
        if (s == "seed-to-soil") return SEED_SOIL_FLAG;
        if (s == "soil-to-fertilizer") return SOIL_FERTILIZER_FLAG;
        if (s == "fertilizer-to-water") return FERTILIZER_WATER_FLAG;
        if (s == "water-to-light") return WATER_LIGHT_FLAG;
        if (s == "light-to-temperature") return LIGHT_TEMP_FLAG;
        if (s == "temperature-to-humidity") return TEMP_HUMIDITY_FLAG;
        if (s == "humidity-to-location") return HUMIDITY_LOCATION_FLAG;
        return INVALID_FLAG;
    }

    static SourceDestMapper generateMapper(const std::string& s) {
        std::vector<std::string> tokens = split(s, " ");
        long source = std::stol(tokens[1]);
        long destination = std::stol(tokens[0]);
        long range = std::stol(tokens[2]);
        return {source, destination, range};
    }

    static void sortMappers(std::vector<SourceDestMapper>& mappers) {
        std::sort(mappers.begin(), mappers.end(), [](SourceDestMapper& a, SourceDestMapper& b) {
            return a.getSource() < b.getSource();
        });
    }

    static long mapValue(const long value, std::vector<SourceDestMapper>& mappers) {
        for (size_t i = 0; i < mappers.size(); i++) {
            if (mappers[i].getSource() > value) {
                if (i - 1 == SIZE_T_MAX) {
                    return mappers[0].mapToDestination(value);
                }
                return mappers[i - 1].mapToDestination(value);
            }
        }
        return mappers[mappers.size() - 1].mapToDestination(value);
    }

    static std::vector<RangePair> mapNewRanges(const RangePair& range,
                                                             const std::vector<SourceDestMapper>& mappers) {
        std::vector<RangePair> newRanges;
        RangePair remainingRange = range;
        for (size_t i = 0; i < mappers.size(); i++) {
            SourceDestMapper m = mappers[i];
            if (remainingRange.first > m.getMaxSource()) { // input range to right outside of mapper range
                continue;
            }
            if (remainingRange.first > m.getSource()
                && remainingRange.first < m.getMaxSource()
                && m.getMaxSource() > remainingRange.first
                && m.getMaxSource() < remainingRange.second) { // left input overlap
                newRanges.push_back(m.mapRangeToDestination(remainingRange.first, m.getMaxSource()));
                remainingRange.first = m.getMaxSource() + 1;
            }
            if (m.getSource() > remainingRange.first
                && m.getSource() < remainingRange.second
                && remainingRange.second > m.getSource()
                && remainingRange.second < m.getMaxSource()) { // right input overlap
                newRanges.push_back(m.mapRangeToDestination(m.getSource(), remainingRange.second));
                remainingRange.second = m.getSource() - 1;
            }
            if (m.getSource() <= remainingRange.first
                && m.getMaxSource() >= remainingRange.second) { // complete input overlap by map
                newRanges.push_back(m.mapRangeToDestination(remainingRange.first, remainingRange.second));
                return newRanges;
            }
            if (m.getSource() > remainingRange.first
                && m.getMaxSource() < remainingRange.second) { // complete map overlap by input
                RangePair leftExceedingRange = std::make_pair(remainingRange.first,
                                                                          m.getSource() - 1);
                RangePair rightExceedingRange = std::make_pair(m.getMaxSource() + 1,
                                                                           remainingRange.second);
                newRanges.push_back(m.mapRangeToDestination(m.getSource(), m.getMaxSource()));
                std::vector<RangePair> newLeftRanges = mapNewRanges(leftExceedingRange, mappers);
                std::vector<RangePair> newRightRanges = mapNewRanges(rightExceedingRange, mappers);
                newRanges.insert(newRanges.end(), newLeftRanges.begin(), newLeftRanges.end());
                newRanges.insert(newRanges.end(), newRightRanges.begin(), newRightRanges.end());
                return newRanges;
            }
        }
        newRanges.push_back(remainingRange);
        return newRanges;
    }
};
