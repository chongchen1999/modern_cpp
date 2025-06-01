#include <iostream>
#include <string>
#include <vector>

// 1. 基本折叠表达式示例
template <typename... Args>
auto sum(Args... args) {
    return (... + args); // 一元右折叠 (args1 + args2 + ... + argsN)
}

template <typename... Args>
auto sum_from_zero(Args... args) {
    return (0 + ... + args); // 二元右折叠 (0 + args1 + args2 + ... + argsN)
}

// 2. 不同类型的折叠
template <typename... Args>
auto concatenate(Args... args) {
    return (std::string{} + ... + args); // 字符串连接
}

// 3. 逻辑运算折叠
template <typename... Args>
bool all_true(Args... args) {
    return (... && args); // 逻辑与折叠
}

template <typename... Args>
bool any_true(Args... args) {
    return (... || args); // 逻辑或折叠
}

// 4. 逗号运算符折叠
template <typename... Args>
void print_all(Args... args) {
    (std::cout << ... << args) << "\n"; // 输出折叠
}

template <typename... Args>
void call_all(Args... args) {
    (..., args()); // 调用所有函数对象
}

// 5. 复杂折叠 - 计算平均值
template <typename... Args>
double average(Args... args) {
    constexpr size_t count = sizeof...(Args);
    return (static_cast<double>(args) + ...) / count;
}

// 6. 折叠与vector结合
template <typename... Args>
std::vector<int> create_vector(Args... args) {
    std::vector<int> v;
    (v.push_back(args), ...); // 逗号运算符折叠填充vector
    return v;
}

int main() {
    // 1. 基本折叠表达式示例
    std::cout << "Sum of 1, 2, 3, 4, 5: " << sum(1, 2, 3, 4, 5) << "\n";
    std::cout << "Sum from zero: " << sum_from_zero(1, 2, 3) << "\n\n";

    // 2. 不同类型的折叠
    std::cout << "Concatenated strings: "
              << concatenate(std::string("Hello, "), "world", "! ", "123",
                             "\n\n");

    // 3. 逻辑运算折叠
    std::cout << std::boolalpha;
    std::cout << "All true (true, true, false): " << all_true(true, true, false)
              << "\n";
    std::cout << "Any true (false, false, true): "
              << any_true(false, false, true) << "\n\n";

    // 4. 逗号运算符折叠
    std::cout << "Print all: ";
    print_all(1, " apple", ", ", 2, " bananas", ", ", 3, " oranges\n");

    std::cout << "Calling functions:\n";
    call_all([]() { std::cout << "Function 1\n"; },
             []() { std::cout << "Function 2\n"; },
             []() { std::cout << "Function 3\n"; });
    std::cout << "\n";

    // 5. 复杂折叠
    std::cout << "Average of 1, 2, 3, 4, 5: " << average(1, 2, 3, 4, 5)
              << "\n\n";

    // 6. 折叠与vector结合
    auto vec = create_vector(10, 20, 30, 40, 50);
    std::cout << "Created vector: ";
    for (int n : vec) {
        std::cout << n << " ";
    }
    std::cout << "\n";

    return 0;
}