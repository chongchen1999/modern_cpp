#include <algorithm>  // for heap functions
#include <functional> // for greater<>
#include <iostream>
#include <vector>

void print(const std::vector<int>& v, const std::string& msg = "") {
    std::cout << msg;
    for (int x : v)
        std::cout << x << " ";
    std::cout << "\n";
}

int main() {
    // 初始化一个向量
    std::vector<int> v = {3, 1, 4, 1, 5, 9};

    print(v, "原始数据: ");

    // 创建最大堆（默认）
    std::make_heap(v.begin(), v.end());
    print(v, "构建最大堆后: ");

    // 添加新元素到堆末尾，并调用 push_heap
    v.push_back(6);
    std::push_heap(v.begin(), v.end());
    print(v, "插入 6 后堆结构: ");

    // 弹出堆顶元素（最大值）
    std::pop_heap(v.begin(), v.end()); // 将堆顶移到最后
    int max_val = v.back();            // 获取堆顶元素
    v.pop_back();                      // 删除该元素
    print(v, "弹出最大值后堆结构: ");
    std::cout << "弹出的最大值为: " << max_val << "\n";

    // 对堆进行排序（降序 -> 升序）
    std::make_heap(v.begin(), v.end());
    std::sort_heap(v.begin(), v.end());
    print(v, "排序后（升序）: ");

    // 构建最小堆（使用 greater<>）
    std::vector<int> v2 = {3, 1, 4, 1, 5, 9};
    std::make_heap(v2.begin(), v2.end(), std::greater<>());
    print(v2, "构建最小堆后: ");

    // 插入并维护最小堆
    v2.push_back(0);
    std::push_heap(v2.begin(), v2.end(), std::greater<>());
    print(v2, "插入 0 后最小堆结构: ");

    // 弹出最小堆的堆顶
    std::pop_heap(v2.begin(), v2.end(), std::greater<>());
    int min_val = v2.back();
    v2.pop_back();
    print(v2, "弹出最小值后的堆结构: ");
    std::cout << "弹出的最小值为: " << min_val << "\n";

    return 0;
}