#include <algorithm> // For sort()
#include <iostream>
#include <vector>

// Function to print vector elements
template <typename T>
void printVector(const std::vector<T>& v, const std::string& name) {
    std::cout << name << ": ";
    for (const auto& elem : v) {
        std::cout << elem << " ";
    }
    std::cout << "\nSize: " << v.size() << ", Capacity: " << v.capacity()
              << "\n\n";
}

int main() {
    // 1. Different ways to create vectors
    std::vector<int> emptyVec;       // Empty vector
    std::vector<int> sizedVec(5);    // Vector with 5 elements (0-initialized)
    std::vector<int> initVec(5, 42); // Vector with 5 elements, all 42
    std::vector<int> listVec = {1, 2, 3, 4, 5}; // Initializer list
    std::vector<int> copyVec(listVec);          // Copy constructor

    printVector(emptyVec, "emptyVec");
    printVector(sizedVec, "sizedVec");
    printVector(initVec, "initVec");
    printVector(listVec, "listVec");
    printVector(copyVec, "copyVec");

    // 2. Modifying vectors
    emptyVec.push_back(10);
    emptyVec.push_back(20);
    emptyVec.emplace_back(
        30); // More efficient than push_back for complex types

    listVec.pop_back();                      // Remove last element
    listVec.insert(listVec.begin() + 2, 99); // Insert at position 2
    listVec.erase(listVec.begin() + 1);      // Remove element at position 1

    printVector(emptyVec, "emptyVec after modifications");
    printVector(listVec, "listVec after modifications");

    // 3. Accessing elements
    std::cout << "Element at index 2: " << listVec[2] << std::endl;
    std::cout << "Element at index 2 (using at()): " << listVec.at(2)
              << std::endl;
    std::cout << "First element: " << listVec.front() << std::endl;
    std::cout << "Last element: " << listVec.back() << std::endl;

    // 4. Capacity operations
    std::cout << "\nBefore reserve:\n";
    printVector(emptyVec, "emptyVec");

    emptyVec.reserve(20); // Increase capacity
    std::cout << "After reserve(20):\n";
    printVector(emptyVec, "emptyVec");

    emptyVec.shrink_to_fit(); // Reduce capacity to fit size
    std::cout << "After shrink_to_fit():\n";
    printVector(emptyVec, "emptyVec");

    // 5. Iterating through vectors
    std::cout << "Iterating using index:\n";
    for (size_t i = 0; i < listVec.size(); ++i) {
        std::cout << listVec[i] << " ";
    }
    std::cout << "\n\n";

    std::cout << "Iterating using iterators:\n";
    for (auto it = listVec.begin(); it != listVec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n\n";

    std::cout << "Range-based for loop:\n";
    for (const auto& elem : listVec) {
        std::cout << elem << " ";
    }
    std::cout << "\n\n";

    // 6. Algorithms with vectors
    std::sort(listVec.begin(), listVec.end());
    std::cout << "After sorting:\n";
    printVector(listVec, "listVec");

    auto found = std::find(listVec.begin(), listVec.end(), 99);
    if (found != listVec.end()) {
        std::cout << "Found 99 at position: " << (found - listVec.begin())
                  << "\n";
    }

    // 7. Clearing and checking empty
    listVec.clear();
    std::cout << "\nAfter clear():\n";
    printVector(listVec, "listVec");
    std::cout << "Is listVec empty? " << (listVec.empty() ? "Yes" : "No")
              << "\n";

    return 0;
}