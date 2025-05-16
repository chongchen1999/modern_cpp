#include <algorithm>
#include <functional> // For searchers
#include <iostream>
#include <string>
#include <vector>

// Helper function to print search results
template <typename It>
void print_result(const std::string& name, It result, It end) {
    if (result != end) {
        std::cout << name << " found at position: "
                  << std::distance(end, result) << "\n";
    } else {
        std::cout << name << " not found\n";
    }
}

int main() {
    // Linear search examples
    std::vector<int> data = {5, 3, 8, 1, 9, 4, 7, 2, 6};
    std::vector<int> subseq = {9, 4, 7};
    std::vector<int> values_to_find = {8, 2, 10};

    // 1. std::find - find single value
    auto it = std::find(data.begin(), data.end(), 8);
    print_result("std::find (value 8)", it, data.end());

    // 2. std::find_if - find with predicate
    it = std::find_if(data.begin(), data.end(), [](int x) { return x > 7; });
    print_result("std::find_if (>7)", it, data.end());

    // 3. std::find_first_of - find any of multiple values
    it = std::find_first_of(data.begin(), data.end(), values_to_find.begin(),
                            values_to_find.end());
    print_result("std::find_first_of (8,2,10)", it, data.end());

    // 4. std::search - find subsequence (brute force)
    it = std::search(data.begin(), data.end(), subseq.begin(), subseq.end());
    print_result("std::search (subseq 9,4,7)", it, data.end());

    // 5. Boyer-Moore search (C++17)
    std::string text = "abacadabrabracabracadabrabrabracad";
    std::string pattern = "abracadabra";

    auto searcher = std::boyer_moore_searcher(pattern.begin(), pattern.end());
    auto match = std::search(text.begin(), text.end(), searcher);

    if (match != text.end()) {
        std::cout << "Boyer-Moore found pattern at position: "
                  << std::distance(text.begin(), match) << "\n";
    } else {
        std::cout << "Pattern not found with Boyer-Moore\n";
    }

    // Binary search examples (requires sorted data)
    std::vector<int> sorted_data = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // 6. std::binary_search - check existence
    bool found = std::binary_search(sorted_data.begin(), sorted_data.end(), 5);
    std::cout << "std::binary_search (5): " << (found ? "found" : "not found")
              << "\n";

    // 7. std::lower_bound - first element not less than value
    it = std::lower_bound(sorted_data.begin(), sorted_data.end(), 5);
    print_result("std::lower_bound (5)", it, sorted_data.end());

    // 8. std::upper_bound - first element greater than value
    it = std::upper_bound(sorted_data.begin(), sorted_data.end(), 5);
    print_result("std::upper_bound (5)", it, sorted_data.end());

    // 9. std::equal_range - range of elements equal to value
    auto range = std::equal_range(sorted_data.begin(), sorted_data.end(), 5);
    std::cout << "std::equal_range (5): ["
              << std::distance(sorted_data.begin(), range.first) << ", "
              << std::distance(sorted_data.begin(), range.second) << ")\n";

    // Example with custom comparator and different types
    struct Record {
        int id;
        std::string name;

        bool operator<(int other_id) const { return id < other_id; }
    };

    std::vector<Record> records = {
        {1, "Alice"}, {3, "Bob"}, {5, "Charlie"}, {7, "Dave"}};

    // Search using just the ID without constructing a Record object
    auto record_it =
        std::lower_bound(records.begin(), records.end(), 5,
                         [](const Record& r, int id) { return r.id < id; });

    if (record_it != records.end() && record_it->id == 5) {
        std::cout << "Found record with ID 5: " << record_it->name << "\n";
    } else {
        std::cout << "Record with ID 5 not found\n";
    }

    return 0;
}