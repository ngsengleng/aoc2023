#include "base.h"

class SourceDestMapper {
private:
     long source;
     long destination;
     long maxSource;
public:
    SourceDestMapper(long s, long d, long r) {
        this -> source = s;
        this -> destination = d;
        this -> maxSource = s + r - 1;
    }

    long mapToDestination(long input) {
        if (input < source) {
            return input;
        }
        if (maxSource < input) {
            return input;
        }
        return input + (destination - source);
    }

    RangePair mapRangeToDestination(long left, long right) {
        return std::make_pair(mapToDestination(left), mapToDestination(right));
    }

    long getSource() const {
        return source;
    }

    long getMaxSource() const {
        return maxSource;
    }

};