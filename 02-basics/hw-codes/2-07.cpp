#include <algorithm>
#include <iostream>
#include <vector>

void FillFibonacci(std::vector<int>& v) {
    std::ranges::generate(v, [a = 0, b = 1]() mutable {
        int next = a;
        a = b;
        b = next + b;
        return next;
    });
}

int main() {
    // Example usage
    std::vector<int> fib(10); // Create a vector of size 10
    FillFibonacci(fib);       // Fill it with Fibonacci numbers

    // Print the result
    for (int num : fib) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}