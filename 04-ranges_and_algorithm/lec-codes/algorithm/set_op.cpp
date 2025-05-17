#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
    // Create two sorted ranges (can be sets, multisets, or sorted vectors)
    std::vector<int> A = {1, 1, 1, 4, 5, 8};
    std::vector<int> B = {1, 4, 8};
    std::vector<int> C = {1, 4, 8, 9};
    std::vector<int> D = {2, 8};

    // 1. std::includes - check if one range is a subset of another
    std::cout << "B is subset of A: "
              << std::includes(A.begin(), A.end(), B.begin(), B.end()) << "\n";
    std::cout << "C is subset of A: "
              << std::includes(A.begin(), A.end(), C.begin(), C.end()) << "\n";
    std::cout << "D is subset of A: "
              << std::includes(A.begin(), A.end(), D.begin(), D.end())
              << "\n\n";

    // 2. std::set_intersection - elements present in both ranges
    std::vector<int> intersection;
    std::set_intersection(A.begin(), A.end(), B.begin(), B.end(),
                          std::back_inserter(intersection));
    std::cout << "A ∩ B: ";
    for (int x : intersection)
        std::cout << x << " ";
    std::cout << "\n\n";

    // 3. std::set_union - elements present in either range
    std::vector<int> union_result;
    std::set_union(A.begin(), A.end(), B.begin(), B.end(),
                   std::back_inserter(union_result));
    std::cout << "A ∪ B: ";
    for (int x : union_result)
        std::cout << x << " ";
    std::cout << "\n\n";

    // 4. std::set_difference - elements in A but not in B
    std::vector<int> difference;
    std::set_difference(A.begin(), A.end(), B.begin(), B.end(),
                        std::back_inserter(difference));
    std::cout << "A - B: ";
    for (int x : difference)
        std::cout << x << " ";
    std::cout << "\n\n";

    // 5. std::set_symmetric_difference - elements in either but not both
    std::vector<int> symmetric_diff;
    std::set_symmetric_difference(A.begin(), A.end(), B.begin(), B.end(),
                                  std::back_inserter(symmetric_diff));
    std::cout << "A Δ B: ";
    for (int x : symmetric_diff)
        std::cout << x << " ";
    std::cout << "\n\n";

    // Example with multisets
    std::vector<int> M1 = {1, 1, 2, 3, 4};
    std::vector<int> M2 = {1, 2, 2, 4, 4};

    // Intersection preserves the minimum count
    std::vector<int> m_intersection;
    std::set_intersection(M1.begin(), M1.end(), M2.begin(), M2.end(),
                          std::back_inserter(m_intersection));
    std::cout << "M1 ∩ M2 (multiset): ";
    for (int x : m_intersection)
        std::cout << x << " ";
    std::cout << "\n";

    // Union preserves the maximum count
    std::vector<int> m_union;
    std::set_union(M1.begin(), M1.end(), M2.begin(), M2.end(),
                   std::back_inserter(m_union));
    std::cout << "M1 ∪ M2 (multiset): ";
    for (int x : m_union)
        std::cout << x << " ";
    std::cout << "\n";

    return 0;
}