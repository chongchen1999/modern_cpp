#include <cstdint>
#include <iostream>
#include <stdfloat>

int main() {
    long a = 0x7FFFFFFFFFFFFFFF;          // 9223372036854775807
    std::cout << sizeof(a) << std::endl;  // 8

    uint32_t b = 0xFFFFFFFF;  // 4294967295

    return 0;
}