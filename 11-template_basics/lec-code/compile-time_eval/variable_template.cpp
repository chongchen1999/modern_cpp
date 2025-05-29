#include <iostream>

// 定义变量模板
template <typename T>
constexpr T pi = T{3.1415926535897932385L};

// 非类型模板参数示例
template <int N>
constexpr int fibonacci = fibonacci<N - 1> + fibonacci<N - 2>;

// 模板特化终止递归
template <>
constexpr int fibonacci<0> = 0;

template <>
constexpr int fibonacci<1> = 1;

int main() {
    std::cout << pi<float> << std::endl;  // 输出: 3.14159
    std::cout << pi<double> << std::endl; // 输出: 3.141592653589793

    std::cout << fibonacci<10> << std::endl; // 输出: 55（第10项斐波那契数）
    return 0;
}