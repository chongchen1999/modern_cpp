// constexpr 函数（C++11）
constexpr int add(int a, int b) {
    return a + b;
}

// consteval 函数（C++20）
consteval int mul(int a, int b) {
    return a * b;
}

int main() {
    // constexpr 使用
    constexpr int x = add(1, 2); // 编译期
    int y = add(3, 4);           // 可能运行期

    // consteval 使用
    constexpr int z = mul(5, 6); // 编译期
    // int w = mul(7, 8);         // 错误：非编译期调用

    // consteval Lambda（C++23）
    auto lambda = [](int n) consteval -> int {
        return n * n;
    };
    constexpr int l = lambda(10); // 编译期
    // int m = lambda(20);         // 错误：非编译期调用
    return 0;
}