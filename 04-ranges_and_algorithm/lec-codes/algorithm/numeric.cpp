#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

// Helper function to print a container
template <typename T>
void print(const std::string& name, const T& container) {
    std::cout << name << ": ";
    for (const auto& val : container) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}

// 1. std::iota demonstration
void demo_iota() {
    std::vector<int> v(5);
    std::iota(v.begin(), v.end(), 10); // Fill with 10, 11, 12, 13, 14
    print("iota (start=10)", v);

    std::vector<char> chars(5);
    std::iota(chars.begin(), chars.end(),
              'A'); // Fill with 'A', 'B', 'C', 'D', 'E'
    print("iota (start='A')", chars);
}

// 2. std::adjacent_difference demonstration
void demo_adjacent_difference() {
    std::vector<int> v{2, 4, 6, 8, 10};
    std::vector<int> result(v.size());

    // Default operation (subtraction)
    std::adjacent_difference(v.begin(), v.end(), result.begin());
    print("adjacent_difference (default)", result);

    // With custom operation (multiplication)
    std::adjacent_difference(v.begin(), v.end(), result.begin(),
                             std::multiplies<int>{});
    print("adjacent_difference (multiply)", result);
}

// 3. std::accumulate demonstration
void demo_accumulate() {
    std::vector<int> v{1, 2, 3, 4, 5};

    // Default operation (addition)
    int sum = std::accumulate(v.begin(), v.end(), 0);
    std::cout << "accumulate (sum): " << sum << "\n";

    // With custom operation (multiplication)
    int product =
        std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>{});
    std::cout << "accumulate (product): " << product << "\n";

    // Important note about types
    std::vector<float> floats{0.2f, 0.3f};
    float wrong_sum =
        std::accumulate(floats.begin(), floats.end(), 0); // 0 (int)
    float correct_sum =
        std::accumulate(floats.begin(), floats.end(), 0.f); // 0.5f
    std::cout << "accumulate (wrong float sum): " << wrong_sum << "\n";
    std::cout << "accumulate (correct float sum): " << correct_sum << "\n";
}

// 4. std::partial_sum demonstration
void demo_partial_sum() {
    std::vector<int> v{1, 2, 3, 4, 5};
    std::vector<int> result(v.size());

    // Default operation (addition)
    std::partial_sum(v.begin(), v.end(), result.begin());
    print("partial_sum (default)", result);

    // With custom operation (multiplication)
    std::partial_sum(v.begin(), v.end(), result.begin(),
                     std::multiplies<int>{});
    print("partial_sum (multiply)", result);
}

// 5. std::inner_product demonstration
void demo_inner_product() {
    std::vector<int> a{1, 2, 3};
    std::vector<int> b{4, 5, 6};

    // Default operations (addition and multiplication)
    int dot_product = std::inner_product(a.begin(), a.end(), b.begin(), 0);
    std::cout << "inner_product (dot product): " << dot_product << "\n";

    // With custom operations (addition and addition)
    int sum_of_sums = std::inner_product(a.begin(), a.end(), b.begin(), 0,
                                         std::plus<int>{}, std::plus<int>{});
    std::cout << "inner_product (sum of sums): " << sum_of_sums << "\n";
}

// 6. std::reduce demonstration (C++17)
void demo_reduce() {
    std::vector<int> v{1, 2, 3, 4, 5};

    // Similar to accumulate but order not guaranteed
    int sum = std::reduce(v.begin(), v.end(), 0);
    std::cout << "reduce (sum): " << sum << "\n";

    // With custom operation
    int product = std::reduce(v.begin(), v.end(), 1, std::multiplies<int>{});
    std::cout << "reduce (product): " << product << "\n";
}

// 7. std::inclusive_scan demonstration (C++17)
void demo_inclusive_scan() {
    std::vector<int> v{1, 2, 3, 4, 5};
    std::vector<int> result(v.size());

    // Similar to partial_sum but order not guaranteed
    std::inclusive_scan(v.begin(), v.end(), result.begin());
    print("inclusive_scan (default)", result);

    // With init value
    std::inclusive_scan(v.begin(), v.end(), result.begin(), std::plus<int>{},
                        10);
    print("inclusive_scan (init=10)", result);
}

// 8. std::transform_reduce demonstration (C++17)
void demo_transform_reduce() {
    std::vector<int> a{1, 2, 3};
    std::vector<int> b{4, 5, 6};

    // Similar to inner_product but order not guaranteed
    int dot_product = std::transform_reduce(a.begin(), a.end(), b.begin(), 0);
    std::cout << "transform_reduce (dot product): " << dot_product << "\n";

    // Unary version
    std::vector<int> v{1, 2, 3, 4, 5};
    int sum_of_squares = std::transform_reduce(
        v.begin(), v.end(), 0, std::plus<int>{}, [](int x) { return x * x; });
    std::cout << "transform_reduce (sum of squares): " << sum_of_squares
              << "\n";
}

// 9. std::exclusive_scan demonstration (C++17)
void demo_exclusive_scan() {
    std::vector<int> v{1, 2, 3, 4, 5};
    std::vector<int> result(v.size());

    // Similar to partial_sum but excludes current element
    std::exclusive_scan(v.begin(), v.end(), result.begin(), 0);
    print("exclusive_scan (default)", result);

    // With custom operation
    std::exclusive_scan(v.begin(), v.end(), result.begin(), 10,
                        std::multiplies<int>{});
    print("exclusive_scan (init=10, multiply)", result);
}

// 10. std::transform_inclusive_scan demonstration (C++17)
void demo_transform_inclusive_scan() {
    std::vector<int> v{1, 2, 3, 4, 5};
    std::vector<int> result(v.size());

    // Transform then inclusive scan
    std::transform_inclusive_scan(v.begin(), v.end(), result.begin(),
                                  std::plus<int>{},
                                  [](int x) { return x * x; });
    print("transform_inclusive_scan (sum of squares)", result);
}

// 11. std::transform_exclusive_scan demonstration (C++17)
void demo_transform_exclusive_scan() {
    std::vector<int> v{1, 2, 3, 4, 5};
    std::vector<int> result(v.size());

    // Transform then exclusive scan
    std::transform_exclusive_scan(v.begin(), v.end(), result.begin(), 0,
                                  std::plus<int>{},
                                  [](int x) { return x * x; });
    print("transform_exclusive_scan (sum of squares)", result);
}

// 12. std::gcd and std::lcm demonstration (C++17)
void demo_gcd_lcm() {
    int a = 24, b = 36;

    std::cout << "gcd(" << a << ", " << b << "): " << std::gcd(a, b) << "\n";
    std::cout << "lcm(" << a << ", " << b << "): " << std::lcm(a, b) << "\n";

    // Edge cases
    std::cout << "gcd(0, 5): " << std::gcd(0, 5) << "\n";
    std::cout << "lcm(0, 5): " << std::lcm(0, 5) << "\n";
}

// 13. std::midpoint demonstration (C++20)
void demo_midpoint() {
    // With integers
    int a = 10, b = 20;
    std::cout << "midpoint(" << a << ", " << b << "): " << std::midpoint(a, b)
              << "\n";

    // With floating point
    float x = 10.5f, y = 20.7f;
    std::cout << "midpoint(" << x << ", " << y << "): " << std::midpoint(x, y)
              << "\n";

    // With pointers
    int arr[] = {0, 1, 2, 3, 4};
    int* p1 = arr;
    int* p2 = std::end(arr);
    std::cout << "midpoint between first and last array elements: "
              << *std::midpoint(p1, p2) << "\n";
}

int main() {
    std::cout << "=== Numeric Algorithms Demonstration ===\n\n";

    demo_iota();
    std::cout << "\n";

    demo_adjacent_difference();
    std::cout << "\n";

    demo_accumulate();
    std::cout << "\n";

    demo_partial_sum();
    std::cout << "\n";

    demo_inner_product();
    std::cout << "\n";

    demo_reduce();
    std::cout << "\n";

    demo_inclusive_scan();
    std::cout << "\n";

    demo_transform_reduce();
    std::cout << "\n";

    demo_exclusive_scan();
    std::cout << "\n";

    demo_transform_inclusive_scan();
    std::cout << "\n";

    demo_transform_exclusive_scan();
    std::cout << "\n";

    demo_gcd_lcm();
    std::cout << "\n";

    demo_midpoint();

    return 0;
}