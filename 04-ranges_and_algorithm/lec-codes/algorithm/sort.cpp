#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

void print_vector(const std::vector<int>& v) {
    for (int num : v) {
        std::cout << num << " ";
    }
    std::cout << "\n";
}

int main() {
    // Create a random vector
    std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    std::cout << "Original vector: ";
    print_vector(v);

    // 1. std::is_sorted
    bool is_sorted = std::is_sorted(v.begin(), v.end());
    std::cout << "Is vector sorted? " << (is_sorted ? "Yes" : "No") << "\n";

    // 2. std::is_sorted_until
    auto sorted_until = std::is_sorted_until(v.begin(), v.end());
    std::cout << "First unsorted element at position: "
              << std::distance(v.begin(), sorted_until) << "\n";

    // 3. std::sort (unstable sort - likely using introsort)
    std::vector<int> v1 = v;
    std::sort(v1.begin(), v1.end());
    std::cout << "After std::sort: ";
    print_vector(v1);

    // 4. std::stable_sort (maintains order of equal elements)
    std::vector<int> v2 = v;
    std::stable_sort(v2.begin(), v2.end());
    std::cout << "After std::stable_sort: ";
    print_vector(v2);

    // 5. std::partial_sort (sort first N elements)
    std::vector<int> v3 = v;
    std::partial_sort(v3.begin(), v3.begin() + 5, v3.end());
    std::cout << "After std::partial_sort (first 5 elements sorted): ";
    print_vector(v3);

    // 6. std::nth_element
    std::vector<int> v4 = v;
    auto mid = v4.begin() + v4.size() / 2;
    std::nth_element(v4.begin(), mid, v4.end());
    std::cout << "After std::nth_element (median is " << *mid << "): ";
    print_vector(v4);

    // 7. std::merge
    std::vector<int> v5(v1.size() + v2.size());
    std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v5.begin());
    std::cout << "After merging two sorted vectors: ";
    print_vector(v5);

    // 8. std::inplace_merge
    std::vector<int> v6 = {1, 3, 5, 7, 2, 4, 6, 8};
    std::cout << "Before inplace_merge: ";
    print_vector(v6);
    std::inplace_merge(v6.begin(), v6.begin() + 4, v6.end());
    std::cout << "After inplace_merge: ";
    print_vector(v6);

    // 9. Custom predicate example
    std::vector<int> v7 = v;
    auto descending = [](int a, int b) { return a > b; };
    std::sort(v7.begin(), v7.end(), descending);
    std::cout << "Sorted in descending order: ";
    print_vector(v7);

    // 10. Demonstration of worst-case scenario for quicksort
    std::vector<int> worst_case(20);
    std::iota(worst_case.begin(), worst_case.end(), 1); // Already sorted
    std::cout << "\nWorst-case scenario for naive quicksort (already sorted): ";
    print_vector(worst_case);
    std::cout << "But std::sort handles it well (uses introsort): ";
    std::sort(worst_case.begin(), worst_case.end());
    print_vector(worst_case);

    return 0;
}