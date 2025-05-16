#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

// Helper function to print vector contents
template <typename T>
void print_vector(const std::vector<T>& vec, const std::string& label) {
    std::cout << label << ": ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

// Implementation of unique algorithm to show how it works internally
template <typename Iterator>
Iterator my_unique(Iterator first, Iterator last) {
    // Handle empty range
    if (first == last) {
        return last;
    }

    // 'before' points to the last element in the result range
    Iterator before = first;

    // Start 'after' from the second element
    Iterator after = first;
    ++after;

    while (after != last) {
        // If current element is different from the last one in result range
        if (!(*before == *after)) {
            // Move 'before' to the next position and copy/move *after to
            // *before
            ++before;
            if (before != after) {
                *before = std::move(*after);
            }
        }
        // Always advance 'after'
        ++after;
    }

    // Return one past the last valid element in the result range
    return ++before;
}

// Implementation of remove algorithm to show how it works internally
template <typename Iterator, typename T>
Iterator my_remove(Iterator first, Iterator last, const T& value) {
    // Find first element to remove
    Iterator result = std::find(first, last, value);

    // If no elements to remove, just return last
    if (result == last) {
        return last;
    }

    // 'result' points to where we'll store the next non-removed element
    Iterator current = result;
    ++current;

    while (current != last) {
        // If current element should not be removed
        if (!(*current == value)) {
            // Move it to the result position
            *result = std::move(*current);
            ++result;
        }
        ++current;
    }

    return result;
}

// Simple implementation of rotate using reverse method
template <typename Iterator>
void my_rotate_reverse(Iterator first, Iterator middle, Iterator last) {
    // Reverse [first, middle)
    std::reverse(first, middle);

    // Reverse [middle, last)
    std::reverse(middle, last);

    // Reverse the entire range [first, last)
    std::reverse(first, last);
}

int main() {
    // ======= std::unique =======
    std::cout << "===== UNIQUE ALGORITHM DEMO =====" << std::endl;

    std::vector<int> vec1 = {1, 1, 4, 5, 3, 3, 3};
    print_vector(vec1, "Original vector");

    // Using standard unique
    auto it1 = std::unique(vec1.begin(), vec1.end());
    print_vector(vec1, "After std::unique");
    std::cout << "Number of unique elements: "
              << std::distance(vec1.begin(), it1) << std::endl;

    // The values after 'it1' are unspecified
    std::cout << "Erasing remaining elements using erase()..." << std::endl;
    vec1.erase(it1, vec1.end());
    print_vector(vec1, "After erase");

    // Using our custom implementation
    std::vector<int> vec2 = {1, 1, 4, 5, 3, 3, 3};
    print_vector(vec2, "\nOriginal vector for my_unique");

    auto it2 = my_unique(vec2.begin(), vec2.end());
    print_vector(vec2, "After my_unique");
    std::cout << "Number of unique elements: "
              << std::distance(vec2.begin(), it2) << std::endl;

    vec2.erase(it2, vec2.end());
    print_vector(vec2, "After erase");

    // ======= std::remove =======
    std::cout << "\n===== REMOVE ALGORITHM DEMO =====" << std::endl;

    std::vector<int> vec3 = {1, 3, 5, 3, 7, 9, 3};
    print_vector(vec3, "Original vector");

    // Using standard remove (Erase-remove idiom)
    auto it3 = std::remove(vec3.begin(), vec3.end(), 3);
    print_vector(vec3, "After std::remove(3)");
    std::cout << "Elements remaining: " << std::distance(vec3.begin(), it3)
              << std::endl;

    // Erase the "removed" elements
    vec3.erase(it3, vec3.end());
    print_vector(vec3, "After erase");

    // Since C++20, we can use std::erase
    std::vector<int> vec4 = {1, 3, 5, 3, 7, 9, 3};
    print_vector(vec4, "\nOriginal vector for std::erase");

    // This combines remove and erase in one operation
    auto removed = std::erase(vec4, 3);
    std::cout << "Elements removed: " << removed << std::endl;
    print_vector(vec4, "After std::erase");

    // Using our custom implementation
    std::vector<int> vec5 = {1, 3, 5, 3, 7, 9, 3};
    print_vector(vec5, "\nOriginal vector for my_remove");

    auto it5 = my_remove(vec5.begin(), vec5.end(), 3);
    print_vector(vec5, "After my_remove(3)");

    vec5.erase(it5, vec5.end());
    print_vector(vec5, "After erase");

    // ======= std::rotate =======
    std::cout << "\n===== ROTATE ALGORITHM DEMO =====" << std::endl;

    std::vector<int> vec6 = {1, 2, 3, 4, 5, 6, 7};
    print_vector(vec6, "Original vector");

    // Left rotate by 3 positions
    std::rotate(vec6.begin(), vec6.begin() + 3, vec6.end());
    print_vector(vec6, "After std::rotate (left rotate by 3)");

    // Right rotate using different approach (rotate by size-n)
    std::vector<int> vec7 = {1, 2, 3, 4, 5, 6, 7};
    print_vector(vec7, "\nOriginal vector");

    // To right rotate by 2, left rotate by size-2
    std::rotate(vec7.begin(), vec7.begin() + (vec7.size() - 2), vec7.end());
    print_vector(vec7, "After right rotation by 2");

    // Using our reverse-based rotate implementation
    std::vector<int> vec8 = {1, 2, 3, 4, 5, 6, 7};
    print_vector(vec8, "\nOriginal vector for my_rotate_reverse");

    my_rotate_reverse(vec8.begin(), vec8.begin() + 3, vec8.end());
    print_vector(vec8, "After my_rotate_reverse (left rotate by 3)");

    // ======= std::replace =======
    std::cout << "\n===== REPLACE ALGORITHM DEMO =====" << std::endl;

    std::vector<int> vec9 = {1, 2, 3, 2, 5, 2, 7};
    print_vector(vec9, "Original vector");

    std::replace(vec9.begin(), vec9.end(), 2, 99);
    print_vector(vec9, "After std::replace (2 -> 99)");

// ======= std::shift_left/right ====== (C++20)
#if __cplusplus >= 202002L
    std::cout << "\n===== SHIFT ALGORITHMS DEMO (C++20) =====" << std::endl;

    std::vector<int> vec10 = {1, 2, 3, 4, 5, 6, 7};
    print_vector(vec10, "Original vector");

    auto it10 = std::shift_left(vec10.begin(), vec10.end(), 2);
    // The last 2 elements are now invalid (unspecified values)
    vec10.erase(it10, vec10.end()); // Clean up invalid elements
    print_vector(vec10, "After std::shift_left by 2");

    std::vector<int> vec11 = {1, 2, 3, 4, 5, 6, 7};
    print_vector(vec11, "\nOriginal vector");

    auto it11 = std::shift_right(vec11.begin(), vec11.end(), 2);
    // The first 2 elements are now invalid (unspecified values)
    vec11.erase(vec11.begin(), it11); // Clean up invalid elements
    print_vector(vec11, "After std::shift_right by 2 and cleanup");
#endif

    return 0;
}