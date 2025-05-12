#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <utility>

// 1. 解构结构体
struct Point {
    int x;
    int y;
};

// 2. 返回元组的函数
std::tuple<int, double, std::string> GetTuple() {
    return {42, 3.14, "hello"};
}

int main() {
    // ===== 示例1：解构结构体 =====
    Point p{10, 20};
    auto [x, y] = p; // 结构化绑定
    std::cout << "解构结构体: " << x << ", " << y << std::endl; // 输出: 10, 20

    // ===== 示例2：解构元组 =====
    auto &&[a, b, c] = GetTuple(); // 从函数返回的元组解构
    std::cout << "解构元组: " << a << ", " << b << ", " << c
              << std::endl; // 输出: 42, 3.14, hello

    // ===== 示例3：解构数组 =====
    int arr[3] = {1, 2, 3};
    auto [m, n, k] = arr; // 解构数组
    std::cout << "解构数组: " << m << ", " << n << ", " << k
              << std::endl; // 输出: 1, 2, 3

    // ===== 示例4：解构std::pair =====
    auto pair = std::make_pair("Alice", 25);
    auto [name, age] = pair; // 解构pair
    std::cout << "解构pair: " << name << ", " << age
              << std::endl; // 输出: Alice, 25

    // ===== 示例5：结合范围循环（STL容器） =====
    std::map<std::string, int> people = {{"Bob", 30}, {"Charlie", 35}};
    std::cout << "解构map:" << std::endl;
    for (const auto& [key, value] : people) { // 解构键值对
        std::cout << "  " << key << ": " << value << std::endl;
    }

    // ===== 示例6：引用绑定（修改原数据） =====
    Point p2{100, 200};
    auto& [ref_x, ref_y] = p2; // 绑定到引用
    ref_x = 999;               // 修改原结构体的成员
    std::cout << "引用绑定: " << p2.x << ", " << p2.y
              << std::endl; // 输出: 999, 200

    return 0;
}