#include <algorithm> // for std::for_each
#include <array>
#include <iostream>
#include <span>
#include <vector>

// Function that accepts a span and prints its elements
void print_span(std::span<const int> s) {
    std::cout << "Span contents (" << s.size() << " elements): ";
    for (const auto& elem : s) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}

// Function that modifies elements through a span
void increment_span(std::span<int> s) {
    std::for_each(s.begin(), s.end(), [](int& n) { n++; });
}

int main() {
    // 1. Span from C-style array
    int c_array[] = {1, 2, 3, 4, 5};
    std::span<int> span1(c_array);
    print_span(span1);

    // 2. Span from std::array
    std::array<int, 6> std_array = {10, 20, 30, 40, 50, 60};
    std::span<int> span2(std_array);
    print_span(span2);

    // 3. Span from std::vector
    std::vector<int> vec = {100, 200, 300, 400, 500, 600, 700};
    std::span<int> span3(vec);
    print_span(span3);

    // 4. Span operations
    std::cout << "\nSpan operations:\n";

    // Subspan (view of a portion)
    auto subspan = span3.subspan(2, 3); // Start at index 2, length 3
    print_span(subspan);

    // First/last elements
    std::cout << "First element: " << span3.front()
              << ", Last element: " << span3.back() << "\n";

    // Size in bytes
    std::cout << "Size in bytes: " << span3.size_bytes() << "\n";

    // 5. Modification through span
    std::cout << "\nBefore increment: ";
    print_span(span1);
    increment_span(span1);
    std::cout << "After increment:  ";
    print_span(span1);

    // 6. Compile-time sized span (C++20)
    std::span<int, 5> fixed_span(c_array); // Size known at compile-time
    std::cout << "\nFixed-size span (size " << fixed_span.size() << "): ";
    print_span(fixed_span);

    // 7. Empty span
    std::span<int> empty_span;
    std::cout << "\nEmpty span is "
              << (empty_span.empty() ? "empty" : "not empty") << "\n";

    return 0;
}