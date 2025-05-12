#include <iostream>

int main() {
    auto res = 1 <=> 2;
    std::cout << "Result of 1 <=> 2: " << (res < 0) << std::endl;
}