#include <iostream>
#include <list>

int main() {
    // 创建 l1，包含10个5
    std::list<int> l1(10, 5);

    // 创建 l2，包含 {2, 1, 4}
    std::list<int> l2 = {2, 1, 4};

    // 将 l2 融合到 l1，之后 l2 会变为空
    l1.merge(l2);

    // 打印当前 l1 和 l2
    std::cout << "After merge:\nl1: ";
    for (int val : l1)
        std::cout << val << ' ';
    std::cout << "\nl2 (should be empty): ";
    for (int val : l2)
        std::cout << val << ' ';
    std::cout << '\n';

    // 去除相邻重复元素
    l1.unique();

    // 排序
    l1.sort();

    // 打印最终结果
    std::cout << "Final l1 (after unique and sort): ";
    for (int val : l1)
        std::cout << val << ' ';
    std::cout << '\n';

    return 0;
}
