#include <iostream>
#include <type_traits>

template <typename T>
constexpr auto process(T value) {
    if constexpr (std::is_integral_v<T>) {
        return value * 2;
    } else {
        return value + 0.5;
    }
}

consteval int onlyAtCompileTime() {
    return 42; // 这个函数只能用于编译期
}

constexpr int evalCheck() {
    if (std::is_constant_evaluated()) {
        return 100;
    } else {
        return 200;
    }
}

constexpr int testIfConsteval() {
    if
        consteval {
            return onlyAtCompileTime(); // 只有在常量上下文下才会执行
        }
    else {
        return 999; // 如果不是常量求值，就走这条路径
    }
}

int main() {
    // constexpr if 示例
    std::cout << "process(10): " << process(10) << "\n";     // 输出 20
    std::cout << "process(3.14): " << process(3.14) << "\n"; // 输出 3.64

    // is_constant_evaluated 示例
    constexpr int a = evalCheck(); // a = 100，因为是编译期求值
    std::cout << "evalCheck() at runtime: " << evalCheck() << "\n"; // 输出 200

    // if consteval 示例
    constexpr int b = testIfConsteval(); // b = 42
    std::cout << "testIfConsteval() at runtime: " << testIfConsteval()
              << "\n"; // 输出 999
}
