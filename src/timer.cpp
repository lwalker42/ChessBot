#include <chrono>
#include "timer.hpp"


using namespace std::chrono;

int elapsed = 0;
time_point<high_resolution_clock> start;

void start_time() {
    start = high_resolution_clock::now();
}

void end_time() {
    elapsed += duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
}