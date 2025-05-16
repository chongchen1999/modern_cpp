#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

// 辅助函数：打印容器内容
template <typename T>
void print(const std::string& msg, const std::vector<T>& v) {
    std::cout << msg << ": ";
    for (const auto& x : v)
        std::cout << x << " ";
    std::cout << "\n";
}

int main() {
    std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};

    // ====================== 1. 算术运算函数对象 ======================
    std::cout << "1. Arithmetic Functors:\n";
    std::cout << "add(3, 5) = " << std::plus<int>{}(3, 5) << "\n";       // 8
    std::cout << "mul(3, 5) = " << std::multiplies<int>{}(3, 5) << "\n"; // 15
    std::cout << "neg(5) = " << std::negate<int>{}(5) << "\n\n";         // -5

    // ====================== 2. 比较运算函数对象 ======================
    std::cout << "2. Comparison Functors:\n";
    std::cout << "gt(3, 5) = " << std::greater<int>{}(3, 5)
              << "\n"; // 0 (false)
    std::cout << "le(3, 5) = " << std::less_equal<int>{}(3, 5)
              << "\n\n"; // 1 (true)

    // 使用 greater 对容器降序排序
    std::sort(v.begin(), v.end(), std::greater<int>{});
    print("Sorted (descending)", v); // 9 6 5 4 3 2 1 1

    // ====================== 3. 逻辑运算函数对象 ======================
    std::cout << "\n3. Logical Functors:\n";
    std::cout << "land(true, false) = " << std::logical_and<bool>{}(true, false)
              << "\n"; // 0
    std::cout << "lnot(true) = " << std::logical_not<bool>{}(true)
              << "\n\n"; // 0

    // ====================== 4. 位运算函数对象 ======================
    std::cout << "4. Bitwise Functors:\n";
    std::cout << "bxor(0b1010, 0b1100) = " << std::bit_xor<int>{}(10, 12)
              << "\n"; // 6 (0b0110)
    std::cout << "bnot(0b1010) = " << std::bit_not<int>{}(10)
              << "\n\n"; // -11 (补码)

    // ====================== 5. 其他工具函数对象 ======================
    // 5.1 std::hash
    std::cout << "5.1 std::hash: \"hello\" = "
              << std::hash<std::string>{}("hello") << "\n";

    // 5.2 std::identity (C++20)
    std::cout << "5.2 std::identity: " << std::identity{}(42) << "\n\n";

    // ====================== 6. 适配器 ======================
    // 6.1 std::bind: 绑定参数
    auto add_10 = std::bind(std::plus<int>{}, 10, std::placeholders::_1);
    std::cout << "6.1 std::bind: add_10(5) = " << add_10(5) << "\n"; // 15

    // 6.2 std::not_fn: 逻辑取反
    auto is_odd = [](int x) { return x % 2 != 0; };
    auto is_even = std::not_fn(is_odd);
    std::cout << "6.2 std::not_fn: is_even(5) = " << is_even(5) << "\n\n";

    // ====================== 综合示例 ======================
    // 使用算术和比较函数对象计算绝对值大于3的元素的乘积
    auto abs_gt_3 = [](int x) { return std::greater<int>{}(std::abs(x), 3); };

    int product =
        std::accumulate(v.begin(), v.end(), 1, [&abs_gt_3](int acc, int x) {
            return abs_gt_3(x) ? std::multiplies<int>()(acc, x) : acc;
        });

    std::cout << "Product of elements with |x| > 3: " << product
              << "\n"; // 9 * 6 * 5 * 4=1080

    return 0;
}