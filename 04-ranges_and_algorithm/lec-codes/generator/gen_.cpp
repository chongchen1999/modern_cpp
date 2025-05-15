#include <iostream>
#include <generator>  // 需要包含这个头文件

// 使用 std::generator 定义生成器
std::generator<int> range(int start, int end) {
    for (int i = start; i < end; ++i) {
        co_yield i;
    }
}

int main() {
    for (int i : range(1, 10)) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}