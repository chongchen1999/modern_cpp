#include <functional>
#include <iostream>

void print_sum(int a, int b, int c) {
    std::cout << "Sum: " << (a + b + c) << std::endl;
}

int main() {
    // 绑定第一个参数为10
    auto bind1 =
        std::bind(print_sum, 10, std::placeholders::_1, std::placeholders::_2);
    bind1(20, 30); // 输出: Sum: 60

    auto lambda1 = [](int b, int c) { print_sum(10, b, c); };
    lambda1(20, 30); // 输出: Sum: 60

    // 绑定第一个和第三个参数
    auto bind2 =
        std::bind(print_sum, std::placeholders::_2, 100, std::placeholders::_1);
    bind2(50, 200); // 相当于 print_sum(200, 100, 50)
    // 输出: Sum: 350

    auto lambda2 = [](int a, int b) { print_sum(b, 100, a); };
    lambda2(50, 200); // 输出: Sum: 350

    // 绑定所有参数
    auto bind3 = std::bind(print_sum, 1, 2, 3);
    bind3(); // 输出: Sum: 6

    auto lambda3 = []() { print_sum(1, 2, 3); };
    lambda3(); // 输出: Sum: 6

    return 0;
}