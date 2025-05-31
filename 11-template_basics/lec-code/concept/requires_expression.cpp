#include <array>
#include <concepts>
#include <iostream>
#include <string>
#include <type_traits>

/////////////////////////////////////////////////////////////
// Note1: 对模板参数进行约束，可以使用简洁写法（concept替代 typename）
/////////////////////////////////////////////////////////////

// 使用标准库 concept：std::integral（约束为整数类型）
template <std::integral T>
T square(T x) {
    return x * x;
}

/////////////////////////////////////////////////////////////
// Note2: concept 可作为布尔表达式使用
/////////////////////////////////////////////////////////////

template <typename T>
void print_type_info() {
    if constexpr (std::integral<T>) {
        std::cout << "Type is integral.\n";
    } else if constexpr (std::floating_point<T>) {
        std::cout << "Type is floating point.\n";
    } else {
        std::cout << "Unknown type category.\n";
    }
}

/////////////////////////////////////////////////////////////
// Note3: NTTP（非类型模板参数）也可以使用 concept
/////////////////////////////////////////////////////////////

// 限制 N 必须为正整数
template <std::size_t N>
requires(N > 0) struct PositiveArray {
    std::array<int, N> data;
};

/////////////////////////////////////////////////////////////
// Note4: concept 是语法约束，不是语义约束
/////////////////////////////////////////////////////////////

template <typename T>
concept Incrementable = requires(T x) {
    ++x; // 检查能否进行 ++x 操作（语法上）
};

// 编译能通过，但不代表“语义上有意义”
struct WeirdType {
    WeirdType& operator++() {
        std::cout << "Incrementing WeirdType\n";
        return *this;
    }
};

// 虽然通过 Incrementable，但没有实际“计数”含义
void use_incrementable(Incrementable auto x) {
    ++x;
}

/////////////////////////////////////////////////////////////
// Note5: 标准库中已有大量 concepts，如 std::integral, std::same_as 等
/////////////////////////////////////////////////////////////

template <typename T, typename U>
requires std::same_as<T, U> // 只接受完全相同类型
void show_same_type(const T& a, const U& b) {
    std::cout << "Types are the same: " << a << ", " << b << "\n";
}

/////////////////////////////////////////////////////////////
// main 测试
/////////////////////////////////////////////////////////////

int main() {
    // Note1: 简写模板参数约束
    std::cout << "square(5) = " << square(5) << "\n"; // OK
    // square(5.5);  // 编译错误：double 不是 integral

    // Note2: concept 用作布尔表达式
    print_type_info<int>();
    print_type_info<float>();
    print_type_info<std::string>();

    // Note3: NTTP + concept
    PositiveArray<3> arr3; // OK
    // PositiveArray<0> arr0; // 编译错误：N 不满足约束 N > 0

    // Note4: concept 是语法检查，不管语义
    WeirdType w;
    use_incrementable(w); // 编译通过，但语义不一定合理

    // Note5: 标准库 concept 的应用
    show_same_type(42, 100); // OK
    // show_same_type(42, 3.14);      // 编译错误：类型不相同

    return 0;
}
