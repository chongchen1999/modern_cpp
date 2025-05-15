#include <algorithm>
#include <iostream>
#include <vector>

// 函数对象 (functor)
struct Square {
    int operator()(int x) const { return x * x; }
};

// 模板函数接受任何可调用对象
template <typename Func>
void transform_and_print(std::vector<int>& vec, Func func) {
    for (auto& num : vec) {
        num = func(num);
    }

    for (const auto& num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 使用lambda表达式
    transform_and_print(numbers,
                        [](int x) { return x * 2; }); // 输出: 2 4 6 8 10

    // 使用函数对象
    Square square;
    transform_and_print(numbers, square); // 输出: 4 16 36 64 100

    // 使用普通函数
    transform_and_print(numbers,
                        [](int x) { return x / 2; }); // 输出: 2 8 18 32 50

    return 0;
}