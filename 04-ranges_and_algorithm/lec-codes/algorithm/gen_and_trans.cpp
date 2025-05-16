#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

// Helper function to print a vector
template <typename T>
void print_vector(const std::string& name, const std::vector<T>& vec) {
    std::cout << name << ": ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main() {
    // ============ FILL & FILL_N ============
    std::vector<int> v1(10);
    std::cout << "=== Fill & Fill_n Example ===" << std::endl;

    // Fill all elements with 5
    std::fill(v1.begin(), v1.end(), 5);
    print_vector("After fill(5)", v1);

    // Fill first 5 elements with 9
    std::fill_n(v1.begin(), 5, 9);
    print_vector("After fill_n(9)", v1);

    // ============ GENERATE & GENERATE_N ============
    std::vector<int> v2(10);
    std::cout << "\n=== Generate & Generate_n Example ===" << std::endl;

    // Generate a sequence with a stateful lambda
    int value = 1;
    std::generate(v2.begin(), v2.end(), [&value]() { return value *= 2; });
    print_vector("After generate(value*=2)", v2);

    // Reset value and generate first 5 elements
    value = 1;
    std::generate_n(v2.begin(), 5, [&value]() { return value += 10; });
    print_vector("After generate_n(value+=10)", v2);

    // ============ FOR_EACH & FOR_EACH_N ============
    std::vector<int> v3 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "\n=== For_each & For_each_n Example ===" << std::endl;

    print_vector("Original v3", v3);

    // Multiply each element by 2 in-place
    std::for_each(v3.begin(), v3.end(), [](int& n) { n *= 2; });
    print_vector("After for_each(n*=2)", v3);

    // Add 5 to first 5 elements in-place
    std::for_each_n(v3.begin(), 5, [](int& n) { n += 5; });
    print_vector("After for_each_n(n+=5)", v3);

    // Demonstrating return value of for_each
    struct Counter {
        int count = 0;
        void operator()(int) { ++count; }
    };

    Counter result = std::for_each(v3.begin(), v3.end(), Counter());
    std::cout << "for_each counter result: " << result.count << std::endl;

    // ============ TRANSFORM ============
    std::vector<int> v4 = {1, 2, 3, 4, 5};
    std::vector<int> v5(5); // Destination vector, pre-sized
    std::vector<int> v6 = {10, 20, 30, 40, 50};
    std::vector<int> v7(5); // Destination for binary transform

    std::cout << "\n=== Transform Example ===" << std::endl;

    print_vector("Original v4", v4);

    // Unary transform: square each element
    std::transform(v4.begin(), v4.end(), v5.begin(),
                   [](int n) { return n * n; });
    print_vector("After transform to v5 (square)", v5);

    // Unary transform with same source and destination
    std::transform(v4.begin(), v4.end(), v4.begin(),
                   [](int n) { return n * 3; });
    print_vector("After transform in-place (triple)", v4);

    // Binary transform: add elements from v4 and v6
    std::transform(v4.begin(), v4.end(), v6.begin(), v7.begin(),
                   [](int a, int b) { return a + b; });
    print_vector("v4", v4);
    print_vector("v6", v6);
    print_vector("After binary transform to v7 (v4+v6)", v7);

    return 0;
}