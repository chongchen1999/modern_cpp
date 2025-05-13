#include <iostream>
#include <list> // For std::ranges::to example
#include <numeric> // For std::views::iota (used in previous examples, kept for completeness)
#include <ranges>
#include <set> // For std::ranges::to example
#include <string>
#include <tuple> // For std::views::zip
#include <vector>

int main() {
    // C++23 Example 1: std::views::chunk
    std::cout << "--- std::views::chunk example ---" << std::endl;
    std::vector<int> numbers_chunk = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 将 numbers_chunk 分成大小为 3 的块
    auto chunked_view = numbers_chunk | std::views::chunk(3);

    std::cout << "Chunked numbers (size 3):" << std::endl;
    for (auto const& chunk : chunked_view) {
        std::cout << "  Chunk: ";
        for (int n : chunk) {
            std::cout << n << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------------------" << std::endl << std::endl;

    // C++23 Example 2: std::views::zip
    std::cout << "--- std::views::zip example (with structured binding) ---"
              << std::endl;
    std::vector<int> numbers_zip = {1, 2, 3, 4, 5};
    std::vector<char> letters_zip = {'a', 'b', 'c', 'd', 'e', 'f'};
    std::vector<std::string> words_zip = {"one", "two", "three"};

    // 将 numbers_zip, letters_zip, 和 words_zip 压缩在一起
    auto zipped_view = std::views::zip(numbers_zip, letters_zip, words_zip);

    std::cout << "Zipped ranges:" << std::endl;
    // Using structured binding to unpack the tuple elements directly
    for (const auto& [num, letter, word] : zipped_view) {
        std::cout << "(" << num << ", " << letter << ", " << word << ")"
                  << std::endl;
    }
    std::cout << "-----------------------------------------------------"
              << std::endl
              << std::endl;

    // C++23 Example 3: std::ranges::to
    std::cout << "--- std::ranges::to example ---" << std::endl;
    std::vector<int> numbers_to = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 过滤偶数，然后转换为 std::list
    std::list<int> even_list =
        numbers_to | std::views::filter([](int n) { return n % 2 == 0; }) |
        std::ranges::to<std::list>();

    std::cout << "Even numbers in a list: ";
    for (int n : even_list) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // 将原始 numbers_to 转换为 std::set (会自动去重和排序)
    std::set<int> numbers_set = numbers_to | std::ranges::to<std::set>();

    std::cout << "Numbers in a set: ";
    for (int n : numbers_set) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    std::cout << "-----------------------------" << std::endl << std::endl;

    // C++23 Example 4: std::views::as_const
    std::cout << "--- std::views::as_const example ---" << std::endl;
    std::vector<int> numbers_as_const = {1, 2, 3, 4, 5};

    auto const_view = numbers_as_const | std::views::as_const;

    std::cout << "Elements via as_const view: ";
    for (const auto& n : const_view) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    std::cout << "------------------------------------" << std::endl
              << std::endl;

    return 0;
}