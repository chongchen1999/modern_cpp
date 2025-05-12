#include <bitset>
#include <iostream>
#include <string>

int main() {
    // ===== 1. 初始化 bitset =====
    std::cout << "===== Initialization =====" << std::endl;

    // 默认构造（所有位为 0）
    std::bitset<8> bs1; // 00000000
    std::cout << "bs1 (default): " << bs1 << std::endl;

    // 从整数初始化
    std::bitset<8> bs2(42); // 42 = 00101010
    std::cout << "bs2 (from int 42): " << bs2 << std::endl;

    // 从字符串初始化（从右向左解析）
    std::bitset<8> bs3("1010"); // 00001010
    std::cout << "bs3 (from string \"1010\"): " << bs3 << std::endl;

    // 从字符串的子串初始化（起始位置，长度）
    std::bitset<8> bs4("11110000", 4); // 取前4位 "1111" -> 00001111
    std::cout << "bs4 (substring \"11110000\", 4): " << bs4 << std::endl;

    // 从字符串（含非'0'/'1'字符时，会抛出 std::invalid_argument）
    try {
        std::bitset<8> bs5("12a01010"); // 'a' 非法
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid bitset string: " << e.what() << std::endl;
    }

    // ===== 2. 位操作 =====
    std::cout << "\n===== Bit Operations =====" << std::endl;

    std::bitset<8> bs("11001100");

    // 设置位（set()）
    bs.set(1); // 将第1位（从0开始）设为1
    std::cout << "After set(1): " << bs << std::endl; // 11001110

    // 重置位（reset()）
    bs.reset(6);                                        // 将第6位设为0
    std::cout << "After reset(6): " << bs << std::endl; // 10001110

    // 翻转位（flip()）
    bs.flip(0);                                        // 翻转第0位
    std::cout << "After flip(0): " << bs << std::endl; // 10001111

    // 全部设置/重置/翻转
    bs.set();                                        // 所有位置1
    std::cout << "After set(): " << bs << std::endl; // 11111111

    bs.reset();                                        // 所有位置0
    std::cout << "After reset(): " << bs << std::endl; // 00000000

    bs.flip();                                        // 所有位取反
    std::cout << "After flip(): " << bs << std::endl; // 11111111

    // ===== 3. 位运算 =====
    std::cout << "\n===== Bitwise Operations =====" << std::endl;

    std::bitset<4> a("1100");
    std::bitset<4> b("1010");

    std::cout << "a: " << a << ", b: " << b << std::endl;
    std::cout << "a & b (AND): " << (a & b) << std::endl;           // 1000
    std::cout << "a | b (OR): " << (a | b) << std::endl;            // 1110
    std::cout << "a ^ b (XOR): " << (a ^ b) << std::endl;           // 0110
    std::cout << "~a (NOT): " << (~a) << std::endl;                 // 0011
    std::cout << "a << 1 (Left Shift): " << (a << 1) << std::endl;  // 1000
    std::cout << "b >> 1 (Right Shift): " << (b >> 1) << std::endl; // 0101

    // ===== 4. 查询与测试 =====
    std::cout << "\n===== Queries and Tests =====" << std::endl;

    std::bitset<8> bs5("10100011");

    // 检查是否有任何位为1
    std::cout << "any(): " << bs5.any() << std::endl; // true (1)

    // 检查是否所有位为0
    std::cout << "none(): " << bs5.none() << std::endl; // false (0)

    // 统计1的个数
    std::cout << "count(): " << bs5.count() << std::endl; // 4

    // 总位数
    std::cout << "size(): " << bs5.size() << std::endl; // 8

    // 测试某一位是否为1
    std::cout << "test(2): " << bs5.test(2) << std::endl; // true (1)
    std::cout << "test(3): " << bs5.test(3) << std::endl; // false (0)

    // 访问位（等价于test()，但不检查范围）
    std::cout << "operator[]: " << bs5[0] << ", " << bs5[1]
              << std::endl; // 1, 1

    // ===== 5. 转换 =====
    std::cout << "\n===== Conversions =====" << std::endl;

    std::bitset<8> bs6("11001010");

    // 转换为 unsigned long
    unsigned long ul = bs6.to_ulong();
    std::cout << "to_ulong(): " << ul << std::endl; // 202

    // 转换为 unsigned long long（C++11）
    unsigned long long ull = bs6.to_ullong();
    std::cout << "to_ullong(): " << ull << std::endl; // 202

    // 转换为字符串
    std::string s = bs6.to_string();
    std::cout << "to_string(): " << s << std::endl; // "11001010"

    // 转换为带格式的字符串（如十六进制）
    std::cout << "Hex: 0x" << std::hex << bs6.to_ulong() << std::endl; // 0xca

    // ===== 6. 其他操作 =====
    std::cout << "\n===== Other Operations =====" << std::endl;

    // 比较两个 bitset
    std::bitset<4> x("1010");
    std::bitset<4> y("1010");
    std::cout << "x == y: " << (x == y) << std::endl; // true (1)

    // 输出流支持
    std::cout << "Output stream: " << x << std::endl; // 1010

    // 输入流（从输入读取二进制字符串）
    std::bitset<8> z;
    std::cout << "Enter an 8-bit binary number (e.g., 11001100): ";
    std::cin >> z;
    std::cout << "You entered: " << z << std::endl;

    return 0;
}