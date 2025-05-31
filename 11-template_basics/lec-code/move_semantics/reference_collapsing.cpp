#include <iostream>
#include <type_traits>

template <typename T>
void check_type(T&& arg) {
    if (std::is_lvalue_reference_v<T&&>)
        std::cout << "左值引用" << std::endl;
    else if (std::is_rvalue_reference_v<T&&>)
        std::cout << "右值引用" << std::endl;
    else
        std::cout << "非引用" << std::endl;
}

int main() {
    int x = 42;
    check_type(x);  // 左值引用（T = int&, T&& → int&）
    check_type(42); // 右值引用（T = int, T&& → int&&）
}