#include <iostream>
#include <iterator> // 包含 std::begin 和 std::end
#include <list>
#include <numeric> // 包含 std::accumulate
#include <type_traits> // 包含 std::is_same_v 等类型特性 (可选, 但有助于理解)
#include <vector>

// 模板函数 Function
template <typename Range>
void Function(Range& range) {
    // 使用 std::begin 和 std::end 获取迭代器
    // 这样可以同时适用于 STL 容器和 C 风格数组
    auto it_begin = std::begin(range);
    auto it_end = std::end(range);

    // 检查范围是否为空
    if (it_begin == it_end) {
        std::cout << "提供的范围是空的。" << std::endl;
        std::cout << "元素修改后的状态: [空]" << std::endl;
        std::cout << "元素总和: 0" << std::endl;
        std::cout << "--------------------------" << std::endl;
        return;
    }

    // 1. 将第一个元素乘以 2
    *it_begin *= 2;

    // 2. 累加所有元素
    //    使用 std::iterator_traits 获取元素的类型
    using ElementType =
        typename std::iterator_traits<decltype(it_begin)>::value_type;
    //    使用 std::accumulate 计算总和，初始值为 ElementType 的零值
    ElementType sum = std::accumulate(it_begin, it_end, ElementType{0});
    //    注意: 如果 ElementType 是较小的整数类型 (如 char, short)，
    //    并且元素数量较多或值较大，累加过程中可能会发生溢出。
    //    在这种情况下，可能需要将累加和的类型显式指定为一个更大的类型，
    //    例如：long long sum = std::accumulate(it_begin, it_end, 0LL);

    // 输出修改后的元素和总和
    std::cout << "元素修改后的状态: ";
    for (auto it = it_begin; it != it_end; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "元素总和: " << sum << std::endl;
    std::cout << "--------------------------" << std::endl;
}

// 测试主函数
int main() {
    std::cout << "测试 std::vector<int>:" << std::endl;
    std::vector<int> v{1, 2, 3};
    Function(v);
    // 预期：第一个元素 1*2=2。修改后元素: 2 2 3。总和: 2+2+3=7

    std::cout << "\n测试 std::list<int>:" << std::endl;
    std::list<int> l{1, 2, 3};
    Function(l);
    // 预期：第一个元素 1*2=2。修改后元素: 2 2 3。总和: 2+2+3=7

    std::cout << "\n测试 C 风格数组 int[]:" << std::endl;
    int arr[]{1, 2, 3}; // arr 的类型是 int[3]
    Function(arr);      // Range& range 会被推导为 int(&)[3] range
                   // 因此 std::begin(arr) 和 std::end(arr) 可以正确工作
    // 预期：第一个元素 1*2=2。修改后元素: 2 2 3。总和: 2+2+3=7

    std::cout << "\n测试 std::vector<double>:" << std::endl;
    std::vector<double> vd{1.5, 2.5, 3.5};
    Function(vd);
    // 预期：第一个元素 1.5*2=3.0。修改后元素: 3.0 2.5 3.5。总和: 3.0+2.5+3.5=9.0

    std::cout << "\n测试空的 std::vector<int>:" << std::endl;
    std::vector<int> empty_v{};
    Function(empty_v);
    // 预期：提供的范围是空的。元素修改后的状态: [空]。元素总和: 0

    std::cout << "\n测试只有一个元素的 std::vector<int>:" << std::endl;
    std::vector<int> single_v{10};
    Function(single_v);
    // 预期：第一个元素 10*2=20。修改后元素: 20。总和: 20

    std::cout << "\n测试 C 风格数组 char[] (字符会转换为整数进行计算):"
              << std::endl;
    char carr[]{'A', 'B', 'C'}; // ASCII: A=65, B=66, C=67
    Function(carr);
    // 'A' (65) * 2 = 130 (通常 char 会提升为 int 进行运算)
    // 如果 char是有符号的且130超出范围，行为可能依赖实现(但通常安全)
    // 预期：第一个元素 65*2=130。修改后元素: (char)130 B C。总和: 130+66+67 =
    // 263 输出字符时，如果130不是可打印字符，可能会显示特殊符号。
    // 为了演示数值，我们可以在循环中强制转换为int打印：
    // for (auto it = std::begin(carr); it != std::end(carr); ++it) {
    //     std::cout << static_cast<int>(*it) << " ";
    // }
    // 但题目要求的是通用模板，默认打印行为即可。

    return 0;
}