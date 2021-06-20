#include <chrono>
#include <iostream>
#include "timer.hpp"


using namespace std::chrono;

double elapsed = 0;
bool running = false;
time_point<high_resolution_clock> start;

void start_time() {
    if (running) {
        std::cout << "TRIED TO START TIMER WHILE IT WAS RUNNING\n";
        return;
    }
    running = true;
    start = high_resolution_clock::now();
}

void end_time() {
    elapsed += duration_cast<nanoseconds>(high_resolution_clock::now() - start).count() / 1000000.;
    running = false;
}