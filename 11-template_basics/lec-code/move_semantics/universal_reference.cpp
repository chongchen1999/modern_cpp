#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

// 1. 普通函数重载版本（更通用的版本）
template <typename T>
void processValue(T& val) {
    std::cout << "处理左值: " << val << std::endl;
}

template <typename T>
void processValue(T&& val) {
    std::cout << "处理右值: " << val << std::endl;
}

// 2. 使用Universal Reference的模板函数
template <typename T>
void processUniversal(T&& val) {
    std::cout << "Universal Reference处理: ";
    processValue(std::forward<T>(val));
}

// 3. 辅助函数展示类型推导
template <typename T>
void showType(T&& val) {
    if (std::is_lvalue_reference<decltype(val)>::value) {
        std::cout << "左值引用类型" << std::endl;
    } else {
        std::cout << "右值引用类型" << std::endl;
    }
}

int main() {
    int a = 10;
    const int b = 20;

    // 测试普通函数
    std::cout << "--- 普通函数测试 ---" << std::endl;
    processValue(a);  // 调用左值版本
    processValue(30); // 调用右值版本
    processValue(b);  // 调用const左值版本

    // 测试Universal Reference
    std::cout << "\n--- Universal Reference测试 ---" << std::endl;
    processUniversal(a);  // T推导为int&
    processUniversal(b);  // T推导为const int&
    processUniversal(30); // T推导为int

    // 测试类型推导
    std::cout << "\n--- 类型推导测试 ---" << std::endl;
    showType(a);  // 左值
    showType(40); // 右值

    // 字符串示例
    std::string s1 = "Hello";
    std::cout << "\n--- 字符串测试 ---" << std::endl;
    processUniversal(s1);            // 左值
    processUniversal(std::move(s1)); // 右值
    processUniversal("World");       // 右值（字符串字面量）

    return 0;
}