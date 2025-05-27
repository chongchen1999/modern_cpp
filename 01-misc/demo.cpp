#include <expected>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

std::expected<int, std::string> parse_number(const std::string& str) {
    try {
        return std::stoi(str);
    } catch (...) {
        return std::unexpected("Invalid number: " + str);
    }
}

int main() {
    std::vector<std::string> data = {"10", "42", "abc", "17", "0"};

    for (const auto& str : data) {
        auto result = parse_number(str);
        if (result) {
            std::cout << "Parsed: " << *result << '\n';
        } else {
            std::cout << "Error: " << result.error() << '\n';
        }
    }

    std::vector<int> numbers = {1, 2, 3, 4, 5, 6};

    auto is_even = [](int n) { return n % 2 == 0; };
    auto square = [](int n) { return n * n; };

    auto transformed =
        numbers | std::views::filter(is_even) | std::views::transform(square);

    std::cout << "Even squares: ";
    for (int n : transformed) {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    return 0;
}
