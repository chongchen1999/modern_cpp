#include <chrono>
#include <functional>
#include <iostream>
#include <random>

// Prevent compiler from optimizing away the calls
volatile int sink = 0;

// Direct call
void direct_call(int (*f)(int), int n) {
    sink = f(n);
}

// std::function call
void std_function_call(std::function<int(int)> f, int n) {
    sink = f(n);
}

int test_func(int x) {
    return x * x;
}

int main() {
    const int iterations = 1e8;
    std::mt19937 rng;
    std::uniform_int_distribution<int> dist(1, 100);

    // Test direct function pointer
    auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        direct_call(test_func, dist(rng));
    }
    auto end1 = std::chrono::high_resolution_clock::now();

    std::cout << "Direct call time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end1 -
                                                                       start1)
                     .count()
              << " ms\n";

    // Test std::function
    auto start2 = std::chrono::high_resolution_clock::now();
    std::function<int(int)> f = test_func;
    for (int i = 0; i < iterations; ++i) {
        std_function_call(f, dist(rng));
    }
    auto end2 = std::chrono::high_resolution_clock::now();

    std::cout << "Function call time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end2 -
                                                                       start2)
                     .count()
              << " ms\n";

    // Prevent sink from being optimized away
    std::cout << "Sink value: " << sink << "\n";
}