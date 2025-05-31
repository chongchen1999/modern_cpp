#include <concepts>
#include <iostream>

// 基础概念：任何算术类型（int, float, double...）
template <typename T>
concept Number = std::is_arithmetic_v<T>;

// 更严格的概念：必须是整数类型（int, short, long...）
template <typename T>
concept Integer = Number<T> && std::integral<T>;

// 重载1：适用于所有 Number（包括 float, double...）
template <typename T>
requires Number<T>
void process(T num) {
    std::cout << "Processing Number: " << num << std::endl;
}

// 重载2：仅适用于 Integer（int, short, long...）
void process(Integer auto num) {
    std::cout << "Processing Integer: " << num << std::endl;
}

int main() {
    process(42);   // 调用 Integer 版本（更匹配）
    process(3.14); // 调用 Number 版本（Integer 不匹配）
    process(10u);  // 调用 Integer 版本（unsigned int 也是整数）
}