#include <concepts>
#include <iostream>

// 定义一个 concept，要求类型 T 支持加法运算符 +
template <typename T>
concept Addable = requires(T a, T b) {
    // 表达式 a + b 必须存在，且结果可转换为 T
    { a + b } -> std::convertible_to<T>;
};

// 仅当 T 满足 Addable 的约束时，函数模板才会参与重载解析
template <typename T>
requires Addable<T> T add(T a, T b) {
    return a + b;
}

int main() {
    std::cout << "3 + 4 = " << add(3, 4) << '\n';         // int 是 Addable
    std::cout << "1.5 + 2.3 = " << add(1.5, 2.3) << '\n'; // double 也是 Addable
    // std::cout << add("Hello, ", "World!");  // ❌ 不合法：const char* 不是
    // Addable
    return 0;
}
