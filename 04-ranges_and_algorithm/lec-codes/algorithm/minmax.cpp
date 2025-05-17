#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <vector>

// 1. 演示std::min和std::max的基本用法
void demo_min_max() {
    int a = 5, b = 3;

    // 使用默认的operator<
    std::cout << "std::min(5, 3) = " << std::min(a, b) << std::endl;
    std::cout << "std::max(5, 3) = " << std::max(a, b) << std::endl;

    // 使用自定义比较函数
    auto cmp = [](int x, int y) { return x > y; }; // 反向比较
    std::cout << "std::min(5, 3, cmp) = " << std::min(a, b, cmp) << std::endl;
    std::cout << "std::max(5, 3, cmp) = " << std::max(a, b, cmp) << std::endl;
}

// 2. 演示std::minmax的用法
void demo_minmax() {
    int a = 5, b = 3;

    // 返回一个pair，first是最小值，second是最大值
    auto result = std::minmax(a, b);
    std::cout << "std::minmax(5, 3) = (" << result.first << ", "
              << result.second << ")" << std::endl;

    // 当值相等时，返回第一个参数
    int c = 5;
    auto result2 = std::minmax(a, c);
    std::cout << "std::minmax(5, 5) = (" << result2.first << ", "
              << result2.second << ")" << std::endl;
}

// 3. 演示使用初始化列表
void demo_initializer_list() {
    // 返回列表中的最小值和最大值
    std::cout << "std::min({1, 2, 3, 4, 5}) = " << std::min({1, 2, 3, 4, 5})
              << std::endl;
    std::cout << "std::max({1, 2, 3, 4, 5}) = " << std::max({1, 2, 3, 4, 5})
              << std::endl;

    auto result = std::minmax({1, 2, 3, 4, 5});
    std::cout << "std::minmax({1, 2, 3, 4, 5}) = (" << result.first << ", "
              << result.second << ")" << std::endl;
}

// 4. 演示min/max_element的用法
void demo_minmax_element() {
    std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};

    // 查找最小元素的迭代器
    auto min_it = std::min_element(v.begin(), v.end());
    std::cout << "min element is at position " << (min_it - v.begin())
              << " with value " << *min_it << std::endl;

    // 查找最大元素的迭代器
    auto max_it = std::max_element(v.begin(), v.end());
    std::cout << "max element is at position " << (max_it - v.begin())
              << " with value " << *max_it << std::endl;

    // 同时查找最小和最大元素
    auto minmax_it = std::minmax_element(v.begin(), v.end());
    std::cout << "minmax_element: min at " << (minmax_it.first - v.begin())
              << " (" << *minmax_it.first << "), max at "
              << (minmax_it.second - v.begin()) << " (" << *minmax_it.second
              << ")" << std::endl;
}

// 5. 演示std::clamp的用法
void demo_clamp() {
    int value = 15;
    int low = 10;
    int high = 20;

    std::cout << "std::clamp(15, 10, 20) = " << std::clamp(value, low, high)
              << std::endl;

    value = 5;
    std::cout << "std::clamp(5, 10, 20) = " << std::clamp(value, low, high)
              << std::endl;

    value = 25;
    std::cout << "std::clamp(25, 10, 20) = " << std::clamp(value, low, high)
              << std::endl;

    // 在边界值的情况
    value = 10;
    std::cout << "std::clamp(10, 10, 20) = " << std::clamp(value, low, high)
              << std::endl;
}

// 6. 演示自定义比较函数的用法
void demo_custom_comparator() {
    struct Person {
        std::string name;
        int age;

        bool operator<(const Person& other) const { return age < other.age; }
    };

    Person alice{"Alice", 30};
    Person bob{"Bob", 25};
    Person charlie{"Charlie", 35};

    // 使用默认的operator<
    auto youngest = std::min(alice, bob);
    std::cout << "Youngest person is " << youngest.name << std::endl;

    // 使用自定义比较函数 - 按名字长度比较
    auto name_length_cmp = [](const Person& a, const Person& b) {
        return a.name.length() < b.name.length();
    };

    auto shortest_name = std::min({alice, bob, charlie}, name_length_cmp);
    std::cout << "Person with shortest name is " << shortest_name.name
              << std::endl;
}

int main() {
    std::cout << "=== Demo std::min and std::max ===" << std::endl;
    demo_min_max();

    std::cout << "\n=== Demo std::minmax ===" << std::endl;
    demo_minmax();

    std::cout << "\n=== Demo initializer list ===" << std::endl;
    demo_initializer_list();

    std::cout << "\n=== Demo min/max_element ===" << std::endl;
    demo_minmax_element();

    std::cout << "\n=== Demo std::clamp ===" << std::endl;
    demo_clamp();

    std::cout << "\n=== Demo custom comparator ===" << std::endl;
    demo_custom_comparator();

    return 0;
}