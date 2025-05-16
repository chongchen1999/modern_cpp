#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>
#include <vector>

int main() {
    // Sample data
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Predicate: check if number is even
    auto is_even = [](int n) { return n % 2 == 0; };

    // 1. std::is_partitioned - check if range is partitioned
    bool initially_partitioned =
        std::is_partitioned(data.begin(), data.end(), is_even);
    std::cout << "Initially partitioned? "
              << (initially_partitioned ? "Yes" : "No") << "\n\n";

    // 2. std::partition - partition the range
    std::vector<int> data1 = data;
    auto partition_point = std::partition(data1.begin(), data1.end(), is_even);

    std::cout << "After std::partition:\n";
    std::cout << "Even numbers (first partition): ";
    std::copy(data1.begin(), partition_point,
              std::ostream_iterator<int>(std::cout, " "));

    std::cout << "\nOdd numbers (second partition): ";
    std::copy(partition_point, data1.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n\n";

    // 3. std::stable_partition - partition while preserving order
    std::vector<int> data2 = data;
    auto stable_partition_point =
        std::stable_partition(data2.begin(), data2.end(), is_even);

    std::cout << "After std::stable_partition:\n";
    std::cout << "Even numbers (first partition, order preserved): ";
    std::copy(data2.begin(), stable_partition_point,
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\nOdd numbers (second partition, order preserved): ";
    std::copy(stable_partition_point, data2.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n\n";

    // 4. std::partition_copy - copy partitions to different locations
    std::vector<int> evens, odds;
    std::partition_copy(data.begin(), data.end(), std::back_inserter(evens),
                        std::back_inserter(odds), is_even);

    std::cout << "After std::partition_copy:\n";
    std::cout << "Even numbers: ";
    std::copy(evens.begin(), evens.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\nOdd numbers: ";
    std::copy(odds.begin(), odds.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n\n";

    // 5. std::partition_point - find partition point in already partitioned
    // range
    auto found_partition_point =
        std::partition_point(data2.begin(), data2.end(), is_even);
    std::cout << "Partition point in stable partitioned data: "
              << *found_partition_point << " at position "
              << (found_partition_point - data2.begin()) << "\n";

    return 0;
}