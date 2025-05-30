#include <iostream>
#include <type_traits>

// 1. 基本模板函数
template <typename T>
void printType(T value) {
    std::cout << "Generic template: " << value << " (type: " << typeid(T).name()
              << ")\n";
}

// 2. 函数重载 - 非模板函数
void printType(int value) {
    std::cout << "Overloaded function for int: " << value << "\n";
}

// 3. 模板特化 - 为const char*类型特化
template <>
void printType<const char*>(const char* value) {
    std::cout << "Specialization for const char*: \"" << value << "\"\n";
}

// 4. 部分特化 - 通过SFINAE实现的类似部分特化效果
template <typename T>
void printType(
    T* value,
    typename std::enable_if<!std::is_same<T, char>::value>::type* = nullptr) {
    std::cout << "Pointer to non-char type: " << *value
              << " (type: " << typeid(T).name() << "*)\n";
}

template <typename T>
void foo(T x) {
    std::cout << "Generic foo: " << x << "\n";
}

template <typename T>
void foo(T* x) {
    std::cout << "Pointer foo: " << *x << "\n";
}

template <typename T>
class MyClass {
public:
    void print() {
        std::cout << "MyClass with type: " << typeid(T).name() << "\n";
    }
};

template <typename T>
class MyClass<T*> {
public:
    void print() {
        std::cout << "Pointer MyClass with type: " << typeid(T).name() << "*"
                  << "\n";
    }
};

int main() {
    // 测试各种情况
    printType(42);      // 调用非模板重载函数
    printType(3.14);    // 调用通用模板
    printType("Hello"); // 调用const char*特化

    int x = 10;
    printType(&x); // 调用指针版本

    char c = 'A';
    printType(&c); // 调用通用模板(因为char*不匹配指针版本)

    double d = 2.71;
    printType(&d); // 调用指针版本


    int arr[] = {1, 2, 3};
    foo(arr); // 调用指针版本

    MyClass<int*>{}.print(); // 调用通用模板

    return 0;
}