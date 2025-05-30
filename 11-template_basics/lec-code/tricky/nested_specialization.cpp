#include <iostream>
#include <type_traits>

template <typename T>
class SmartContainer {
public:
    // 嵌套的类型萃取模板
    template <typename U>
    struct TypeTraits {
        static constexpr bool is_numeric = std::is_arithmetic_v<U>;
        static constexpr const char* name = "unknown";
    };

    // 偏特化：指针类型 - 这是允许的
    template <typename U>
    struct TypeTraits<U*> {
        static constexpr bool is_numeric = false;
        static constexpr const char* name = "pointer";
    };

    // 偏特化：引用类型 - 这也是允许的
    template <typename U>
    struct TypeTraits<U&> {
        static constexpr bool is_numeric = std::is_arithmetic_v<U>;
        static constexpr const char* name = "reference";
    };

    // 错误示例（注释掉）：不能在非特化的外围模板中定义全特化
    /*
    template<>
    struct TypeTraits<int> {  // 这会导致编译错误
        static constexpr bool is_numeric = true;
        static constexpr const char* name = "integer";
    };
    */
};

// 方法1：为特定的外围模板实例定义全特化
// 必须先特化外围模板，然后特化嵌套模板
template <>
template <>
struct SmartContainer<std::string>::TypeTraits<int> {
    static constexpr bool is_numeric = true;
    static constexpr const char* name = "string_container_int";
};

template <>
template <>
struct SmartContainer<double>::TypeTraits<int> {
    static constexpr bool is_numeric = true;
    static constexpr const char* name = "double_container_int";
};

// 演示完全特化的外围模板中可以定义偏特化
template <>
class SmartContainer<int> {
public:
    template <typename U>
    struct TypeTraits {
        static constexpr bool is_numeric = false;
        static constexpr const char* name = "int_container_unknown";
    };

    // 在完全特化的外围模板中，可以定义偏特化
    template <typename U>
    struct TypeTraits<U*> {
        static constexpr bool is_numeric = false;
        static constexpr const char* name = "int_container_pointer";
    };
};

template <>
struct SmartContainer<int>::TypeTraits<char> {
    static constexpr bool is_numeric = false;
    static constexpr const char* name = "int_container_char";
};

// 另一个例子：演示规则的应用
template <typename T, typename U>
class Outer {
public:
    template <typename V>
    class Inner {
    public:
        static void print() { std::cout << "General Inner" << std::endl; }
    };

    // 偏特化是允许的
    template <typename V>
    class Inner<V*> {
    public:
        static void print() { std::cout << "Pointer Inner" << std::endl; }
    };
};

// 为特定的Outer实例定义Inner的全特化
template <>
template <>
class Outer<int, double>::Inner<char> {
public:
    static void print() {
        std::cout << "Specialized Inner for Outer<int,double> and char"
                  << std::endl;
    }
};

int main() {
    // 测试SmartContainer
    using StringContainer = SmartContainer<std::string>;
    using DoubleContainer = SmartContainer<double>;
    using IntContainer = SmartContainer<int>;

    std::cout << "=== SmartContainer测试 ===" << std::endl;

    // 使用偏特化
    std::cout << "StringContainer::TypeTraits<double*>::name = "
              << StringContainer::TypeTraits<double*>::name << std::endl;

    std::cout << "StringContainer::TypeTraits<double&>::name = "
              << StringContainer::TypeTraits<double&>::name << std::endl;

    // 使用全特化
    std::cout << "StringContainer::TypeTraits<int>::name = "
              << StringContainer::TypeTraits<int>::name << std::endl;

    std::cout << "DoubleContainer::TypeTraits<int>::name = "
              << DoubleContainer::TypeTraits<int>::name << std::endl;

    // 使用完全特化的外围模板
    std::cout << "IntContainer::TypeTraits<float>::name = "
              << IntContainer::TypeTraits<float>::name << std::endl;

    std::cout << "IntContainer::TypeTraits<char*>::name = "
              << IntContainer::TypeTraits<char*>::name << std::endl;

    std::cout << "IntContainer::TypeTraits<char>::name = "
              << IntContainer::TypeTraits<char>::name << std::endl;

    std::cout << "\n=== Outer/Inner测试 ===" << std::endl;

    // 测试Outer/Inner
    Outer<float, int>::Inner<double>::print();  // 使用通用版本
    Outer<float, int>::Inner<double*>::print(); // 使用偏特化
    Outer<int, double>::Inner<char>::print();   // 使用全特化

    return 0;
}