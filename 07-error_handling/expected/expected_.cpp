#include <cmath>
#include <expected>
#include <iostream>
#include <string>

enum class ParseError { InvalidInput, OutOfRange, EmptyString };

std::expected<int, ParseError> parse_integer(const std::string& str) {
    if (str.empty()) {
        return std::unexpected(ParseError::EmptyString);
    }

    try {
        size_t pos;
        int value = std::stoi(str, &pos);

        if (pos != str.size()) {
            return std::unexpected(ParseError::InvalidInput);
        }

        return value;
    } catch (const std::out_of_range&) {
        return std::unexpected(ParseError::OutOfRange);
    } catch (...) {
        return std::unexpected(ParseError::InvalidInput);
    }
}

std::expected<double, ParseError> safe_sqrt(int x) {
    if (x < 0) {
        return std::unexpected(ParseError::OutOfRange);
    }
    return std::sqrt(x);
}

int main() {
    std::string input;
    std::cout << "Enter an integer: ";
    std::cin >> input;

    auto parsed = parse_integer(input);

    auto result = parsed.and_then([](int x) {
        std::cout << "Parsed value: " << x << "\n";
        return safe_sqrt(x);
    });

    if (result) {
        std::cout << "Square root: " << *result << "\n";
    } else {
        switch (result.error()) {
            case ParseError::InvalidInput:
                std::cout << "Error: Invalid input format\n";
                break;
            case ParseError::OutOfRange:
                std::cout << "Error: Number out of range\n";
                break;
            case ParseError::EmptyString:
                std::cout << "Error: Empty input\n";
                break;
        }
    }

    return 0;
}