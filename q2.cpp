#include <iostream>
#include <chrono>
#include <unistd.h>
using namespace std::chrono;

#define NUM_INVOCATIONS 1000000

void simpleFunction() {}

int main() {
    

    // Measure function call overhead
    auto start = high_resolution_clock::now();
    for (int i = 0; i < NUM_INVOCATIONS; i++) {
        simpleFunction();
    }
    auto end = high_resolution_clock::now();
    duration<double> functionTime = duration_cast<duration<double>>(end - start);

    // Measure system call overhead
    start = high_resolution_clock::now();
    for (int i = 0; i < NUM_INVOCATIONS; i++) {
        getpid();
    }
    end = high_resolution_clock::now();
    duration<double> syscallTime = duration_cast<duration<double>>(end - start);

    std::cout << "Average time per function call: " 
              << (functionTime.count() / NUM_INVOCATIONS) * 1e9 << " nanoseconds" << std::endl;
    std::cout << "Average time per system call: " 
              << (syscallTime.count() / NUM_INVOCATIONS) * 1e9 << " nanoseconds" << std::endl;
    std::cout << "Ratio (system call / function call): " 
              << syscallTime.count() / functionTime.count() << std::endl;

    return 0;
}
