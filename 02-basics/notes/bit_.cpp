#include <bit>
#include <bitset>
#include <cstdint>
#include <iostream>

int main() {
    uint32_t num = 0b00010100;  // Binary: 00000000 00000000 00000000 00010100
                                // (20 in decimal)

    // 1. Counting bits
    std::cout << "Number: " << num << " (binary: " << std::bitset<32>(num)
              << ")\n";
    std::cout << "popcount (number of 1 bits): " << std::popcount(num) << "\n";
    std::cout << "countl_zero (leading zeros): " << std::countl_zero(num)
              << "\n";
    std::cout << "countr_zero (trailing zeros): " << std::countr_zero(num)
              << "\n";
    std::cout << "countl_one (leading ones): " << std::countl_one(num) << "\n";
    std::cout << "countr_one (trailing ones): " << std::countr_one(num)
              << "\n\n";

    // 2. Bit rotation
    uint32_t rotated_left = std::rotl(num, 2);   // Rotate left by 2 bits
    uint32_t rotated_right = std::rotr(num, 3);  // Rotate right by 3 bits
    std::cout << "Original: " << std::bitset<8>(num) << "\n";
    std::cout << "rotl by 2: " << std::bitset<8>(rotated_left) << "\n";
    std::cout << "rotr by 3: " << std::bitset<8>(rotated_right) << "\n\n";

    // 3. Endianness
    if constexpr (std::endian::native == std::endian::little) {
        std::cout << "This system is little-endian\n";
    } else if constexpr (std::endian::native == std::endian::big) {
        std::cout << "This system is big-endian\n";
    } else {
        std::cout << "This system has mixed endianness\n";
    }

    // 4. Bit casting (type punning)
    float f = 3.14f;
    auto as_uint = std::bit_cast<uint32_t>(f);
    std::cout << "\nFloat: " << f << " as uint32_t: " << as_uint
              << " (binary: " << std::bitset<32>(as_uint) << ")\n";

    return 0;
}