#ifndef TEST_CONTROLHARDWARE_STOPWATCH_H
#define TEST_CONTROLHARDWARE_STOPWATCH_H

#include <chrono>

class StopWatch {
private:
    chrono::steady_clock::time_point start{chrono::steady_clock::now()};

public:
    StopWatch() = default;

    ~StopWatch() = default;

    long countInSeconds() {
        return chrono::duration_cast<chrono::seconds>
                (chrono::steady_clock::now() - start).count();
    }

    long countInMilliseconds() {
        return chrono::duration_cast<chrono::milliseconds>
                (chrono::steady_clock::now() - start).count();
    };

    void reset() {
        start = chrono::steady_clock::now();
    }
};

#endif //TEST_CONTROLHARDWARE_STOPWATCH_H
