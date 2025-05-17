#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

// Function to demonstrate std::is_permutation
void demonstrate_is_permutation() {
    std::cout << "=== Demonstrating std::is_permutation ===\n";

    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {3, 1, 4, 5, 2};
    std::vector<int> v3 = {1, 2, 3, 4, 6};

    std::cout << "v1: ";
    for (int i : v1)
        std::cout << i << " ";
    std::cout << "\n";

    std::cout << "v2: ";
    for (int i : v2)
        std::cout << i << " ";
    std::cout << "\n";

    std::cout << "v3: ";
    for (int i : v3)
        std::cout << i << " ";
    std::cout << "\n";

    std::cout << "v1 and v2 are permutations: " << std::boolalpha
              << std::is_permutation(v1.begin(), v1.end(), v2.begin(), v2.end()) << "\n";

    std::cout << "v1 and v3 are permutations: " << std::boolalpha
              << std::is_permutation(v1.begin(), v1.end(), v3.begin(), v3.end()) << "\n";

    std::cout << "\n";
}

// Function to demonstrate std::next_permutation
void demonstrate_next_permutation() {
    std::cout << "=== Demonstrating std::next_permutation ===\n";

    std::vector<int> v = {1, 2, 3};

    std::cout << "All permutations of {1, 2, 3} in order:\n";

    // To get all permutations, we need to start with the sorted sequence
    do {
        for (int i : v)
            std::cout << i << " ";
        std::cout << "\n";
    } while (std::next_permutation(v.begin(), v.end()));

    std::cout << "\n";
}

// Function to demonstrate std::prev_permutation
void demonstrate_prev_permutation() {
    std::cout << "=== Demonstrating std::prev_permutation ===\n";

    std::vector<int> v = {3, 2, 1};

    std::cout << "All permutations of {3, 2, 1} in reverse order:\n";

    // To get all permutations in reverse order, start with reverse sorted
    // sequence
    do {
        for (int i : v)
            std::cout << i << " ";
        std::cout << "\n";
    } while (std::prev_permutation(v.begin(), v.end()));

    std::cout << "\n";
}

// Function to demonstrate the behavior at boundary permutations
void demonstrate_boundary_behavior() {
    std::cout << "=== Demonstrating Boundary Behavior ===\n";

    std::vector<int> v1 = {1, 2, 3}; // First permutation
    std::vector<int> v2 = {3, 2, 1}; // Last permutation

    std::cout
        << "Attempting prev_permutation on first permutation {1, 2, 3}:\n";
    bool result1 = std::prev_permutation(v1.begin(), v1.end());
    std::cout << "Result: " << result1
              << " (false means no previous permutation exists)\n";
    std::cout << "Vector remains: ";
    for (int i : v1)
        std::cout << i << " ";
    std::cout << "\n\n";

    std::cout << "Attempting next_permutation on last permutation {3, 2, 1}:\n";
    bool result2 = std::next_permutation(v2.begin(), v2.end());
    std::cout << "Result: " << result2
              << " (false means no next permutation exists)\n";
    std::cout << "Vector remains: ";
    for (int i : v2)
        std::cout << i << " ";
    std::cout << "\n\n";
}

// Function to demonstrate custom comparator with permutations
void demonstrate_custom_comparator() {
    std::cout << "=== Demonstrating Custom Comparator ===\n";

    std::vector<int> v1 = {1, 2, 3, 4};
    std::vector<int> v2 = {4, 3, 2, 1};
    std::vector<int> v3 = {0, 0, 1, 1};

    // Custom comparator that considers numbers equal if their parity is same
    auto parity_compare = [](int a, int b) { return (a % 2) == (b % 2); };

    std::cout << "v1: ";
    for (int i : v1)
        std::cout << i << " ";
    std::cout << "\n";

    std::cout << "v2: ";
    for (int i : v2)
        std::cout << i << " ";
    std::cout << "\n";

    std::cout << "Are v1 and v2 permutations under parity comparison? "
              << std::boolalpha
              << std::is_permutation(v1.begin(), v1.end(), v3.begin(), v3.end(),
                                     parity_compare)
              << "\n\n";
}

int main() {
    demonstrate_is_permutation();
    demonstrate_next_permutation();
    demonstrate_prev_permutation();
    demonstrate_boundary_behavior();
    demonstrate_custom_comparator();

    return 0;
}