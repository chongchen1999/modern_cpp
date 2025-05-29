#include <print>
#include <vector>
#include <string>

int main() {
    std::println("Size of std::vector<int>: {}", sizeof(std::vector<int>));
    std::println("Size of std::vector<std::string>: {}", sizeof(std::vector<std::string>));

    std::println("Size of std::string: {}", sizeof(std::string));
    return 0;
}