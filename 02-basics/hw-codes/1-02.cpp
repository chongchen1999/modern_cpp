#include <cstdint>
#include <iostream>

int main() {
    std::uint8_t value = 42;
    std::cout << reinterpret_cast<void*>(&value) << '\n';
}