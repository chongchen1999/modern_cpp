#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

// 自定义模板类演示 CTAD
template <typename T, typename U>
class MyPair {
public:
    MyPair(T first, U second) : first_(first), second_(second) {}

    void print() const {
        std::cout << "MyPair(" << first_ << ", " << second_ << ")\n";
    }

    T first_;
    U second_;
};

// 为 MyPair 添加推导指引
MyPair(const char*, const char*)->MyPair<std::string, std::string>;

// 别名模板演示 Alias Template Deduction (C++20)
template <typename T>
using NumberVector = std::vector<T>;

int main() {
    // 1. 标准库中的 CTAD 示例 (C++17)
    std::vector numbers{1, 2, 3, 4, 5}; // 推导为 std::vector<int>
    std::cout << "numbers type: vector<int> with size " << numbers.size()
              << "\n";

    std::pair p(42, "hello"); // 推导为 std::pair<int, const char*>
    std::cout << "pair: (" << p.first << ", " << p.second << ")\n";

    // 2. 自定义类的 CTAD 示例
    MyPair mp1(10, 3.14); // 推导为 MyPair<int, double>
    mp1.print();

    // 使用推导指引得到 MyPair<std::string, std::string>
    MyPair mp2{"hello", "world"};
    mp2.print();

    // 3. 别名模板推导示例 (C++20)
    NumberVector nv{1.1, 2.2, 3.3}; // 推导为 NumberVector<double>
    std::cout << "NumberVector size: " << nv.size() << "\n";

    std::map<std::string, int> skm{{"apple", 10}, {"banana", 20}};
    std::cout << "StringKeyMap size: " << skm.size() << "\n";

    // 4. 更复杂的例子：智能指针与容器
    auto ptr =
        std::make_shared<std::vector<int>>(numbers); // CTAD 用于 make_shared
    std::cout << "shared_ptr<vector<int>> use_count: " << ptr.use_count()
              << "\n";

    // 5. 嵌套模板的 CTAD
    std::vector strings{"one", "two", "three"}; // std::vector<const char*>
    std::vector<std::vector<int>> matrix{{1, 2}, {3, 4}}; // 显式指定

    // 6. 结构化绑定与 CTAD
    auto [x, y] = MyPair{100, 200.5}; // 推导为 MyPair<int, double>
    std::cout << "Structured binding: x=" << x << ", y=" << y << "\n";

    return 0;
}