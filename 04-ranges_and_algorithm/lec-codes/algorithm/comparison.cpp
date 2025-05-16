#include <algorithm>
#include <compare> // for std::strong_ordering
#include <iostream>
#include <string>
#include <vector>

int main() {
    // Example vectors for comparison
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {1, 2, 3, 4, 5};
    std::vector<int> v3 = {1, 2, 3, 4, 6};
    std::vector<int> v4 = {1, 2, 3, 4};
    std::vector<int> v5 = {1, 2, 4, 3};
    std::vector<int> v6 = {-1, 2, -3, 4, -5};

    // 1. std::equal examples
    std::cout << "std::equal examples:\n";
    // Compare v1 and v2 (same size and elements)
    bool eq1 = std::equal(v1.begin(), v1.end(), v2.begin());
    std::cout << "v1 == v2: " << std::boolalpha << eq1 << "\n";

    // Compare v1 and v4 (different size)
    bool eq2 = std::equal(v1.begin(), v1.end(), v4.begin());
    std::cout << "v1 == v4: " << eq2
              << "\n"; // false, but dangerous if v4 is smaller

    // Safe way to compare with different size ranges
    bool eq3 = std::equal(v1.begin(), v1.end(), v4.begin(), v4.end());
    std::cout << "v1 == v4 (safe): " << eq3 << "\n";

    // With custom predicate (compare absolute values)
    bool eq4 =
        std::equal(v1.begin(), v1.end(), v6.begin(), v6.end(),
                   [](int a, int b) { return std::abs(a) == std::abs(b); });
    std::cout << "v1 == v6 (abs): " << eq4 << "\n\n";

    // 2. std::lexicographical_compare examples
    std::cout << "std::lexicographical_compare examples:\n";
    // Compare v1 and v3 (v1 is "less than" v3)
    bool lc1 = std::lexicographical_compare(v1.begin(), v1.end(), v3.begin(),
                                            v3.end());
    std::cout << "v1 < v3: " << lc1 << "\n";

    // Compare v3 and v1 (v3 is not "less than" v1)
    bool lc2 = std::lexicographical_compare(v3.begin(), v3.end(), v1.begin(),
                                            v1.end());
    std::cout << "v3 < v1: " << lc2 << "\n";

    // Compare v1 and v4 (v4 is prefix of v1)
    bool lc3 = std::lexicographical_compare(v1.begin(), v1.end(), v4.begin(),
                                            v4.end());
    std::cout << "v1 < v4: " << lc3 << "\n";

    // With custom predicate (compare squares)
    bool lc4 = std::lexicographical_compare(
        v1.begin(), v1.end(), v5.begin(), v5.end(),
        [](int a, int b) { return a * a < b * b; });
    std::cout << "v1 < v5 (squared): " << lc4 << "\n\n";

    // 3. std::lexicographical_compare_three_way (C++20)
    std::cout << "std::lexicographical_compare_three_way examples:\n";
    // Compare v1 and v2 (equal)
    auto lc3w1 = std::lexicographical_compare_three_way(v1.begin(), v1.end(),
                                                        v2.begin(), v2.end());
    std::cout << "v1 <=> v2: ";
    if (lc3w1 == 0)
        std::cout << "equal\n";
    else if (lc3w1 < 0)
        std::cout << "less\n";
    else
        std::cout << "greater\n";

    // Compare v1 and v3 (v1 is less than v3)
    auto lc3w2 = std::lexicographical_compare_three_way(v1.begin(), v1.end(),
                                                        v3.begin(), v3.end());
    std::cout << "v1 <=> v3: ";
    if (lc3w2 == 0)
        std::cout << "equal\n";
    else if (lc3w2 < 0)
        std::cout << "less\n";
    else
        std::cout << "greater\n";

    // Compare v3 and v1 (v3 is greater than v1)
    auto lc3w3 = std::lexicographical_compare_three_way(v3.begin(), v3.end(),
                                                        v1.begin(), v1.end());
    std::cout << "v3 <=> v1: ";
    if (lc3w3 == 0)
        std::cout << "equal\n";
    else if (lc3w3 < 0)
        std::cout << "less\n";
    else
        std::cout << "greater\n\n";

    // 4. std::mismatch examples
    std::cout << "std::mismatch examples:\n";
    // Find first mismatch between v1 and v3
    auto mismatch1 = std::mismatch(v1.begin(), v1.end(), v3.begin());
    std::cout << "First mismatch between v1 and v3 at position: "
              << (mismatch1.first - v1.begin()) << "\n";
    std::cout << "v1 has " << *mismatch1.first << ", v3 has "
              << *mismatch1.second << "\n";

    // Safe version with both ranges specified
    auto mismatch2 = std::mismatch(v1.begin(), v1.end(), v4.begin(), v4.end());
    std::cout << "First mismatch between v1 and v4 at position: "
              << (mismatch2.first - v1.begin()) << "\n";

    // With custom predicate (compare parity)
    auto mismatch3 = std::mismatch(v1.begin(), v1.end(), v5.begin(),
                                   [](int a, int b) { return a % 2 == b % 2; });
    std::cout << "First parity mismatch between v1 and v5 at position: "
              << (mismatch3.first - v1.begin()) << "\n";

    return 0;
}