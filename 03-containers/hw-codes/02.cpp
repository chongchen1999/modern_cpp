#include <algorithm>
#include <compare> // for strong_ordering in C++20
#include <iostream>
#include <iterator>
#include <vector>

void print_vector(const std::vector<int>& v) {
    std::ostream_iterator<int> out(std::cout, " ");
    std::copy(v.begin(), v.end(), out);
    std::cout << '\n';
}

int main() {
    // 创建 v1 包含 10 个 5
    std::vector<int> v1(10, 5);

    // 创建 v2 包含 {2,1,4}
    std::vector<int> v2 = {2, 1, 4};

    // 反向插入 v2 到 v1 的第 3 个位置
    v1.insert(v1.begin() + 2, v2.rbegin(),
              v2.rend()); // 注意反向插入顺序为 4,1,2

    std::cout << "After reverse insertion: ";
    print_vector(v1); // 输出结果: 5 5 4 1 2 5 5 5 5 5 5 5 5

    // 移除从第5个元素开始的所有元素
    v1.erase(v1.begin() + 5, v1.end());

    std::cout << "After erase from 5th element: ";
    print_vector(v1); // 输出结果: 5 5 4 1 2

    // 移除所有奇数（使用 erase-remove 惯用法，避免 O(n^2)）
    v1.erase(
        std::remove_if(v1.begin(), v1.end(), [](int x) { return x % 2 == 1; }),
        v1.end());

    std::cout << "After removing odd numbers: ";
    print_vector(v1); // 输出结果: 4 2

    // 与 {1, 7} 做三路比较
    std::vector<int> v = {1, 7};

#if __cpp_impl_three_way_comparison >= 201907L // 检查是否支持C++20比较
    auto cmp = v1 <=> v;
    if (cmp < 0)
        std::cout << "v1 < v\n";
    else if (cmp > 0)
        std::cout << "v1 > v\n";
    else
        std::cout << "v1 == v\n";
#else
    if (v1 < v)
        std::cout << "v1 < v\n";
    else if (v1 > v)
        std::cout << "v1 > v\n";
    else
        std::cout << "v1 == v\n";
#endif

    return 0;
}
