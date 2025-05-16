#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

void demonstrate_copy() {
    std::vector<int> source = {1, 2, 3, 4, 5};
    std::vector<int> destination(source.size());

    std::copy(source.begin(), source.end(), destination.begin());

    std::cout << "std::copy result: ";
    for (int x : destination)
        std::cout << x << " ";
    std::cout << "\n\n";
}

void demonstrate_copy_if() {
    std::vector<int> source = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> evens;

    std::copy_if(source.begin(), source.end(), std::back_inserter(evens),
                 [](int x) { return x % 2 == 0; });

    std::cout << "std::copy_if (even numbers): ";
    for (int x : evens)
        std::cout << x << " ";
    std::cout << "\n\n";
}

void demonstrate_copy_n() {
    std::vector<int> source = {10, 20, 30, 40, 50};
    std::vector<int> destination(3); // Copy first 3 elements

    std::copy_n(source.begin(), 3, destination.begin());

    std::cout << "std::copy_n (first 3 elements): ";
    for (int x : destination)
        std::cout << x << " ";
    std::cout << "\n\n";
}

void demonstrate_copy_backward() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8};

    // Shift elements 2-5 to positions 3-6
    std::copy_backward(vec.begin() + 2, vec.begin() + 5, vec.begin() + 6);

    std::cout << "std::copy_backward (shift elements): ";
    for (int x : vec)
        std::cout << x << " ";
    std::cout << "\n\n";
}

void demonstrate_remove_copy() {
    std::vector<int> numbers = {1, 2, 3, 2, 4, 2, 5, 2};
    std::vector<int> result;

    std::remove_copy(numbers.begin(), numbers.end(), std::back_inserter(result),
                     2);

    std::cout << "std::remove_copy (remove 2s): ";
    for (int x : result)
        std::cout << x << " ";
    std::cout << "\n\n";
}

void demonstrate_remove_copy_if() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> result;

    std::remove_copy_if(numbers.begin(), numbers.end(),
                        std::back_inserter(result),
                        [](int x) { return x % 2 == 0; });

    std::cout << "std::remove_copy_if (remove evens): ";
    for (int x : result)
        std::cout << x << " ";
    std::cout << "\n\n";
}

void demonstrate_unique_copy() {
    std::vector<int> duplicates = {1, 1, 2, 2, 2, 3, 4, 4, 5};
    std::vector<int> result;

    std::unique_copy(duplicates.begin(), duplicates.end(),
                     std::back_inserter(result));

    std::cout << "std::unique_copy (remove consecutive duplicates): ";
    for (int x : result)
        std::cout << x << " ";
    std::cout << "\n\n";
}

void demonstrate_reverse_copy() {
    std::vector<int> source = {1, 2, 3, 4, 5};
    std::vector<int> result;

    std::reverse_copy(source.begin(), source.end(), std::back_inserter(result));

    std::cout << "std::reverse_copy: ";
    for (int x : result)
        std::cout << x << " ";
    std::cout << "\n\n";
}

void demonstrate_rotate_copy() {
    std::vector<int> source = {1, 2, 3, 4, 5};
    std::vector<int> result;

    // Rotate left by 2 positions
    std::rotate_copy(source.begin(), source.begin() + 2, source.end(),
                     std::back_inserter(result));

    std::cout << "std::rotate_copy (rotate left by 2): ";
    for (int x : result)
        std::cout << x << " ";
    std::cout << "\n\n";
}

void demonstrate_replace_copy() {
    std::vector<int> source = {1, 2, 3, 2, 4, 2, 5};
    std::vector<int> result;

    std::replace_copy(source.begin(), source.end(), std::back_inserter(result),
                      2, 20);

    std::cout << "std::replace_copy (2 -> 20): ";
    for (int x : result)
        std::cout << x << " ";
    std::cout << "\n\n";
}

void demonstrate_replace_copy_if() {
    std::vector<int> source = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> result;

    std::replace_copy_if(
        source.begin(), source.end(), std::back_inserter(result),
        [](int x) { return x % 2 == 0; }, 0);

    std::cout << "std::replace_copy_if (evens -> 0): ";
    for (int x : result)
        std::cout << x << " ";
    std::cout << "\n\n";
}

int main() {
    demonstrate_copy();
    demonstrate_copy_if();
    demonstrate_copy_n();
    demonstrate_copy_backward();
    demonstrate_remove_copy();
    demonstrate_remove_copy_if();
    demonstrate_unique_copy();
    demonstrate_reverse_copy();
    demonstrate_rotate_copy();
    demonstrate_replace_copy();
    demonstrate_replace_copy_if();

    return 0;
}