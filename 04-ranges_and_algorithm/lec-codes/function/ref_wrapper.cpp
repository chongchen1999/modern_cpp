#include <algorithm>
#include <functional> // 提供 std::reference_wrapper, std::ref, std::cref
#include <iostream>
#include <vector>

// 1. 修改被包装引用的函数
void increment(int& x) {
    x += 10;
}

// 2. 打印函数（展示const引用包装）
void print(const int& x) {
    std::cout << x << " ";
}

int main() {
    int a = 1, b = 2, c = 3;

    // ===== 场景1：存储引用到容器 =====
    std::vector<std::reference_wrapper<int>> ref_vec;
    ref_vec.push_back(std::ref(a)); // 包装a的引用
    ref_vec.push_back(std::ref(b)); // 包装b的引用
    ref_vec.emplace_back(c);        // 隐式构造包装器（C++17起）

    std::cout << "原始值: ";
    for (int x : {a, b, c})
        std::cout << x << " "; // 输出: 1 2 3
    std::cout << "\n";

    // 通过reference_wrapper修改值
    for (auto& ref : ref_vec) {
        ref.get() *= 2; // 解引用并修改
    }

    std::cout << "修改后: " << a << " " << b << " " << c << "\n"; // 输出: 2 4 6

    // ===== 场景2：传递引用到泛型函数 =====
    // auto bound_increment = std::bind(increment, std::ref(a)); // 绑定到a的引用
    auto bound_increment = [&a] { increment(std::ref(a)); }; // 使用lambda捕获并修改引用
    bound_increment();                         // 调用后 a += 10
    std::cout << "bind后a的值: " << a << "\n"; // 输出: 12

    // ===== 场景3：与STL算法结合 =====
    std::for_each(ref_vec.begin(), ref_vec.end(), increment); // 每个元素 +=10
    std::cout << "STL算法后: " << a << " " << b << " " << c << "\n"; // 22 14 16

    // ===== 场景4：const引用包装 =====
    const int& const_ref = a;
    auto cref_wrapper = std::cref(const_ref); // 包装const引用
    // cref_wrapper.get() = 100; // 错误：不能修改const引用
    print(cref_wrapper); // 隐式转换为const int&

    // ===== 场景5：重新赋值引用包装器 =====
    std::reference_wrapper<int> ref_wrap = std::ref(b);
    ref_wrap = std::ref(c); // 重新绑定到c的引用（注意：不是修改c的值！）
    ref_wrap.get() = 99;
    std::cout << "\n重新绑定后c的值: " << c << "\n"; // 输出: 99
}