#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

// 示例1：使用SFINAE检查类型是否有size()成员函数
template <typename T, typename = void>
struct has_size : std::false_type {};

template <typename T>
struct has_size<T, std::void_t<decltype(std::declval<T>().size())>>
    : std::true_type {};

template <typename T>
constexpr bool has_size_v = has_size<T>::value;

// 示例2：使用SFINAE进行不同类型的分发处理
template <typename T>
typename std::enable_if_t<std::is_integral_v<T>, void> process(const T& value) {
    std::cout << "处理整数: " << value << " (平方: " << value * value << ")\n";
}

template <typename T>
typename std::enable_if_t<std::is_floating_point_v<T>, void>
process(const T& value) {
    std::cout << "处理浮点数: " << value
              << " (四舍五入: " << static_cast<int>(value + 0.5) << ")\n";
}

template <typename T>
typename std::enable_if_t<!std::is_arithmetic_v<T> && has_size_v<T>, void>
process(const T& value) {
    std::cout << "处理容器类: 大小 = " << value.size() << "\n";
}

template <typename T>
typename std::enable_if_t<!std::is_arithmetic_v<T> && !has_size_v<T>, void>
process(const T& value) {
    std::cout << "处理其他类型: " << typeid(T).name() << "\n";
}

// 示例3：SFINAE用于类模板成员函数
template <typename T>
class Wrapper {
public:
    // 只有T可流输出时才可用的方法
    template <typename U = T>
    auto print() -> std::enable_if_t<
        std::is_same_v<decltype(std::cout << std::declval<U>()), std::ostream&>,
        void> {
        std::cout << "包装值: " << value_ << "\n";
    }

    // 只有T有size()方法时才可用的方法
    template <typename U = T>
    auto show_size() -> std::enable_if_t<has_size_v<U>, void> {
        std::cout << "大小: " << value_.size() << "\n";
    }

    Wrapper(T value) : value_(value) {}

private:
    T value_;
};

int main() {
    // 测试不同类型的分发处理
    process(42);                        // 整数
    process(3.14);                      // 浮点数
    process(std::string("Hello"));      // 有size()的容器类
    process(std::vector<int>{1, 2, 3}); // 容器类
    process(std::cout);                 // 其他类型

    std::cout << "\n";

    // 测试Wrapper类
    Wrapper<int> w1(100);
    w1.print(); // OK - int可流输出
    // w1.show_size(); // 编译错误 - int没有size()

    Wrapper<std::string> w2("SFINAE");
    w2.print();     // OK - string可流输出
    w2.show_size(); // OK - string有size()

    return 0;
}