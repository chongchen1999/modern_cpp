#include <iostream>
#include <type_traits>

int main() {
    // 根据条件选择类型
    using Type1 = std::conditional<true, int, double>::type;  // Type1 是 int
    using Type2 = std::conditional<false, int, double>::type; // Type2 是 double

    std::cout << std::is_same<Type1, int>::value << std::endl; // 输出 1 (true)
    std::cout << std::is_same<Type2, double>::value
              << std::endl; // 输出 1 (true)

    // 也可以使用 C++14 的别名模板版本
    using Type3 = std::conditional_t<(sizeof(int) > 2), int, long>;
    // 如果int大小大于2字节，选择int，否则选择long
}