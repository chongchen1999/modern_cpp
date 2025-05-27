#include <iostream>
#include <stdexcept>

void riskyOperation(int x) {
    if (x < 0) throw std::invalid_argument("Negative value!");
    std::cout << "Operation successful: " << x << std::endl;
}

int main() {
    try {
        riskyOperation(-1); // 抛出异常
    } catch (const std::invalid_argument& e) {
        std::cerr << "Caught: " << e.what() << std::endl;
    }
    return 0;
}