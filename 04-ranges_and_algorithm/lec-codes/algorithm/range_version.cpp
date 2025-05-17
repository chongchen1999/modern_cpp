#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <optional>
#include <ranges>
#include <string>
#include <vector>

namespace rng = std::ranges;
namespace vw = std::views;

// Basic range algorithm usage
void demonstrate_basic_range_algorithms() {
    std::vector<int> vec = {5, 3, 1, 4, 2};

    // Traditional std::sort requires begin/end iterators
    std::sort(vec.begin(), vec.end());

    // Range version is more concise
    rng::sort(vec);

    std::cout << "After sorting: ";
    for (int x : vec)
        std::cout << x << " ";
    std::cout << "\n";
}

// Projection examples
void demonstrate_projections() {
    struct Person {
        std::string name;
        int age;
    };

    std::vector<Person> people = {{"Alice", 30}, {"Bob", 25}, {"Charlie", 35}};

    // Sort by age using projection
    rng::sort(people, {}, &Person::age); // {} means default comparator (less)

    std::cout << "People sorted by age:\n";
    for (const auto& p : people) {
        std::cout << p.name << " (" << p.age << ")\n";
    }

    // Sort by name length using a lambda projection
    rng::sort(people, rng::less{},
              [](const Person& p) { return p.name.size(); });

    std::cout << "\nPeople sorted by name length:\n";
    for (const auto& p : people) {
        std::cout << p.name << " (" << p.name.size() << " letters)\n";
    }
}

// Range algorithm advantages
void demonstrate_range_advantages() {
    // More human-friendly error messages with concepts
    // Uncomment to see the error:
    // rng::sort(42); // Error: 42 is not a range

    // Works with non-common ranges (where begin/end have different types)
    auto odd_numbers =
        vw::iota(1, 10) | vw::filter([](int x) { return x % 2 != 0; });
    std::cout << "\nOdd numbers 1-10: ";
    for (int x : odd_numbers)
        std::cout << x << " ";
    std::cout << "\n";

    // Safety with temporary containers
    // auto result = rng::find(std::vector{1, 2, 3}, 2); // Would compile with
    // std:: auto result = rng::find(std::vector{1, 2, 3}, 2); // Error with
    // ranges: returns std::ranges::dangling
}

// Enhanced min/max functionality
void demonstrate_enhanced_minmax() {
    std::vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6};

    // Traditional std::minmax requires initializer_list or exactly 2 values
    auto [min1, max1] = std::minmax({3, 1, 4});

    // Range version works with any range
    auto [min2, max2] = rng::minmax(nums);

    std::cout << "\nMin/max of nums: " << min2 << "/" << max2 << "\n";
}

// Return value types
void demonstrate_return_types() {
    std::vector<int> src = {1, 2, 3, 4, 5};
    std::vector<int> dest(5);

    // in_out_result example (copy)
    auto [in, out] = rng::copy(src, dest.begin());
    std::cout << "\nCopied " << (in - src.begin()) << " elements\n";

    // in_in_out_result example (merge)
    std::vector<int> v1 = {1, 3, 5};
    std::vector<int> v2 = {2, 4, 6};
    std::vector<int> merged(6);
    auto [in1, in2, out3] = rng::merge(v1, v2, merged.begin());
    std::cout << "Merged result: ";
    for (int x : merged)
        std::cout << x << " ";
    std::cout << "\n";

    // min_max_result example
    auto [min, max] = rng::minmax_element(src);
    std::cout << "Min/max elements: " << *min << "/" << *max << "\n";
}

// Set operations
void demonstrate_set_operations() {
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {3, 4, 5, 6, 7};
    std::vector<int> result(5);

    // Intersection
    auto [in1, in2, out] = rng::set_intersection(v1, v2, result.begin());
    result.resize(out - result.begin());
    std::cout << "\nIntersection: ";
    for (int x : result)
        std::cout << x << " ";
    std::cout << "\n";

    // Using projection
    struct Number {
        int value;
        bool operator<(const Number& other) const {
            return value < other.value;
        }
    };

    std::vector<Number> nums1 = {{1}, {2}, {3}};
    std::vector<Number> nums2 = {{2}, {3}, {4}};
    std::vector<Number> num_result(3);

    rng::set_union(nums1, nums2, num_result.begin(), {}, &Number::value,
                   &Number::value);
    std::cout << "Union (using projection): ";
    for (const auto& n : num_result) {
        if (n.value != 0)
            std::cout << n.value << " ";
    }
    std::cout << "\n";
}

// Numeric algorithms
void demonstrate_numeric_algorithms() {
    std::vector<int> nums = {1, 2, 3, 4, 5};

    // iota - fixed version
    std::vector<int> sequence(5);
    auto [out, val] = rng::iota(sequence.begin(), sequence.end(),
                                10); // Fill with 10, 11, 12, ...
    std::cout << "\nIota result: ";
    for (int x : sequence)
        std::cout << x << " ";
    std::cout << "\n";

    // fold_left (C++23)
    auto sum = rng::fold_left(nums, 0, std::plus{});
    std::cout << "Sum of nums: " << sum << "\n";

    // fold_left_first (C++23)
    auto product = rng::fold_left_first(nums, std::multiplies{});
    std::cout << "Product of nums: " << product.value_or(0) << "\n";

    // fold_left_with_iter (C++23)
    auto [end, result] = rng::fold_left_with_iter(nums, 1, std::multiplies{});
    std::cout << "Product (with iter): " << result << "\n";
}

// New algorithms (C++23)
void demonstrate_new_algorithms() {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::vector<int> sub = {3, 4};

    // contains
    bool has_three = rng::contains(nums, 3);
    std::cout << "\nVector contains 3: " << std::boolalpha << has_three << "\n";

    // contains_subrange
    bool has_sub = rng::contains_subrange(nums, sub);
    std::cout << "Vector contains subrange [3,4]: " << has_sub << "\n";

    // starts_with/ends_with - these are in <string> header, not ranges
    bool starts = std::string("12345").starts_with("12");
    bool ends = std::string("12345").ends_with("45");
    std::cout << "String starts with \"12\": " << starts
              << ", ends with \"45\": " << ends << "\n";

    // find_last
    std::vector<int> dupes = {1, 2, 3, 2, 1};
    auto last_two = rng::find_last(dupes, 2);
    std::cout << "Last 2 is at position: " << (last_two.begin() - dupes.begin())
              << "\n";
}

// Iterator utilities
void demonstrate_iterator_utilities() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // next with bound
    auto it =
        rng::next(vec.begin(), 3, vec.end()); // Safe even if vec.size() < 3
    std::cout << "\nElement at position 3: " << *it << "\n";

    // distance with range
    auto dist = rng::distance(vec);
    std::cout << "Vector size via distance: " << dist << "\n";

    // advance with bound
    auto it2 = vec.begin();
    rng::advance(it2, 2, vec.end());
    std::cout << "After advancing 2: " << *it2 << "\n";
}

int main() {
    demonstrate_basic_range_algorithms();
    demonstrate_projections();
    demonstrate_range_advantages();
    demonstrate_enhanced_minmax();
    demonstrate_return_types();
    demonstrate_set_operations();
    demonstrate_numeric_algorithms();
    demonstrate_new_algorithms();
    demonstrate_iterator_utilities();

    return 0;
}