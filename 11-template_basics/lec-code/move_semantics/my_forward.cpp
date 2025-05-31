#include <iostream>
#include <type_traits>
#include <utility> // 用于比较标准库版本

// 实现 my_move
template <typename T>
constexpr std::remove_reference_t<T>&& my_move(T&& t) noexcept {
    return static_cast<std::remove_reference_t<T>&&>(t);
}

// 实现 my_forward
template <typename T>
constexpr T&& my_forward(std::remove_reference_t<T>& t) noexcept {
    return static_cast<T&&>(t);
}

template <typename T>
constexpr T&& my_forward(std::remove_reference_t<T>&& t) noexcept {
    static_assert(!std::is_lvalue_reference_v<T>,
                  "Cannot forward an rvalue as an lvalue.");
    return static_cast<T&&>(t);
}

// 测试函数
void process(int& x) {
    std::cout << "处理左值: " << x << std::endl;
}

void process(int&& x) {
    std::cout << "处理右值: " << x << std::endl;
}

void process(const int& x) {
    std::cout << "处理const左值: " << x << std::endl;
}

// 包装函数，展示完美转发
template <typename T>
void wrapper(T&& arg) {
    std::cout << "使用my_forward: ";
    process(my_forward<T>(arg));

    std::cout << "使用std::forward: ";
    process(std::forward<T>(arg));

    std::cout << "-------------------" << std::endl;
}

int main() {
    int x = 42;
    const int y = 100;

    std::cout << "========== 测试my_move ==========\n";
    int a = 10;
    int&& b = my_move(a); // 转换为右值引用
    std::cout << "a = " << a << ", b = " << b << std::endl;

    int&& c = std::move(a); // 标准库版本比较
    std::cout << "a = " << a << ", c = " << c << std::endl;

    std::cout << "\n========== 测试my_forward ==========\n";

    // 测试左值
    std::cout << "传递左值:\n";
    wrapper(x);

    // 测试右值
    std::cout << "传递右值:\n";
    wrapper(my_move(x));
    wrapper(200); // 直接传递右值

    // 测试const左值
    std::cout << "传递const左值:\n";
    wrapper(y);

    return 0;
}