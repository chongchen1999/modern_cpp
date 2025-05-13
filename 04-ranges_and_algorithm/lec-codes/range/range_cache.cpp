#include <algorithm> // for std::find_if
#include <iostream>
#include <ranges>
#include <vector>

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Create a filter view to get even numbers
    auto even_view = data | std::views::filter([](int i) {
                         std::cout
                             << "Checking " << i
                             << std::endl; // To show when predicate is called
                         return i % 2 == 0;
                     });

    // --- First iteration (behaves as expected) ---
    std::cout << "First iteration:" << std::endl;
    for (int i : even_view) {
        std::cout << "\n---" << i << "---\n";
    }
    std::cout << "\n\n";

    // --- Modifying the underlying data ---
    // This modification might happen elsewhere in a real program
    // and not be immediately obvious.
    std::cout << "Modifying data..." << std::endl;
    data[1] = 100; // Change 2 to 100 (still even)
    data[3] = 5;   // Change 4 to 5 (now odd)
    data[5] = 101; // Change 6 to 101 (now odd)
    std::cout << "Data modified.\n\n";

    // --- Second iteration (may exhibit unexpected behavior due to caching) ---
    // Depending on the standard library implementation, the begin() iterator
    // might have been cached in the first iteration.
    // The cached begin() might not re-evaluate the predicate for elements
    // it already checked to find the *first* matching element.
    std::cout << "Second iteration after modification:" << std::endl;
    for (int i : even_view) {
        std::cout << "\n---" << i << "---\n";
    }
    std::cout << "\n";

    return 0;
}