#include <algorithm> // For std::sort and std::find
#include <array>     // For std::array (C++11 fixed-size array)
#include <iostream>

// Function to print an array
template <typename T, size_t N>
void printArray(const T (&arr)[N]) {
    std::cout << "Array elements: ";
    for (size_t i = 0; i < N; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

int main() {
    // =============================================
    // 1. Basic Array Declaration and Initialization
    // =============================================
    std::cout << "=== Basic Array Operations ===\n";

    // Declaration of an array with 5 integers (uninitialized)
    int numbers[5];

    // Initialization at declaration
    double temperatures[4] = {36.5, 37.0, 37.5, 36.8};

    // Array with inferred size
    char vowels[] = {'a', 'e', 'i', 'o', 'u'};

    // Printing arrays
    printArray(temperatures);
    printArray(vowels);

    // =============================================
    // 2. Accessing and Modifying Array Elements
    // =============================================
    std::cout << "\n=== Accessing and Modifying Elements ===\n";

    // Accessing elements (0-based indexing)
    std::cout << "First vowel: " << vowels[0] << "\n";
    std::cout << "Third temperature: " << temperatures[2] << "\n";

    // Modifying elements
    temperatures[1] = 36.9;
    vowels[3] = 'y'; // Changing 'o' to 'y'

    std::cout << "Modified temperatures: ";
    printArray(temperatures);
    std::cout << "Modified vowels: ";
    printArray(vowels);

    // =============================================
    // 3. Array Size and Iteration
    // =============================================
    std::cout << "\n=== Array Size and Iteration ===\n";

    // Getting array size (number of elements)
    const size_t tempSize = sizeof(temperatures) / sizeof(temperatures[0]);
    std::cout << "Temperatures array has " << tempSize << " elements\n";

    // Iterating through an array
    std::cout << "Temperatures (using index): ";
    for (size_t i = 0; i < tempSize; ++i) {
        std::cout << temperatures[i] << " ";
    }
    std::cout << "\n";

    // Range-based for loop (C++11)
    std::cout << "Temperatures (range-based): ";
    for (double temp : temperatures) {
        std::cout << temp << " ";
    }
    std::cout << "\n";

    // =============================================
    // 4. Multi-dimensional Arrays
    // =============================================
    std::cout << "\n=== Multi-dimensional Arrays ===\n";

    // 2D array (3x3 matrix)
    int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    std::cout << "Matrix elements:\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }

    // =============================================
    // 5. Arrays and Pointers
    // =============================================
    std::cout << "\n=== Arrays and Pointers ===\n";

    // Array name is essentially a pointer to first element
    int* ptr = numbers; // equivalent to &numbers[0]

    // Pointer arithmetic to access array elements
    *ptr = 10;       // numbers[0] = 10
    *(ptr + 1) = 20; // numbers[1] = 20
    ptr[2] = 30;     // numbers[2] = 30

    std::cout << "Numbers array after pointer modification: ";
    printArray(numbers);

    // =============================================
    // 6. Standard Library Array (C++11)
    // =============================================
    std::cout << "\n=== std::array (C++11) ===\n";

    // Fixed-size array container from standard library
    std::array<int, 5> stdArray = {5, 3, 1, 4, 2};

    // Accessing elements
    std::cout << "First element: " << stdArray.front() << "\n";
    std::cout << "Last element: " << stdArray.back() << "\n";

    // Size information
    std::cout << "Array size: " << stdArray.size() << "\n";
    std::cout << "Is empty? " << (stdArray.empty() ? "Yes" : "No") << "\n";

    // Sorting
    std::sort(stdArray.begin(), stdArray.end());
    std::cout << "Sorted array: ";
    for (int num : stdArray) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // Searching
    auto it = std::find(stdArray.begin(), stdArray.end(), 3);
    if (it != stdArray.end()) {
        std::cout << "Found 3 at position " << (it - stdArray.begin()) << "\n";
    }

    return 0;
}