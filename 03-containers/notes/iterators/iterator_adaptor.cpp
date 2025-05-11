#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges> // 添加这行
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3, 4, 5};

    // 反向迭代器适配器
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        std::cout << *it << " "; // 输出: 5 4 3 2 1
    }
    std::cout << "\n";

    // 插入迭代器适配器
    std::vector<int> dest;
    std::copy(v.begin(), v.end(), std::back_inserter(dest));

    // C++20范围适配器
    auto even = [](int x) { return x % 2 == 0; };
    for (int i : v | std::views::filter(even)) {
        std::cout << i << " "; // 输出: 2 4
    }
    std::cout << "\n";
}