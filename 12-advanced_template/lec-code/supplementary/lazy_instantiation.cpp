#include <iostream>
#include <type_traits>

// 一个简单的模板类
template <typename T>
class MyContainer {
public:
    void process() {
        std::cout << "Processing MyContainer<" << typeid(T).name() << ">"
                  << std::endl;
        // 这里有一个依赖于T的成员函数调用
        // 但只有在实际使用时才会实例化
        T{}.doSomething();
    }
};

// 一个类，有doSomething方法
class ValidType {
public:
    void doSomething() {
        std::cout << "ValidType::doSomething() called" << std::endl;
    }
};

// 另一个类，没有doSomething方法
class InvalidType {
public:
    void someOtherMethod() {
        std::cout << "This method exists but not doSomething()" << std::endl;
    }
};

int main() {
    // 实例化MyContainer<ValidType> - 这是有效的
    MyContainer<ValidType> validContainer;
    validContainer.process(); // 这会正常工作

    // 实例化MyContainer<InvalidType> - 但不会立即出错
    MyContainer<InvalidType> invalidContainer;

    // 关键点：即使InvalidType没有doSomething方法，上面的声明也不会导致编译错误
    // 因为模板的实例化是"惰性"的 - 只有在实际使用时才会检查

    std::cout << "InvalidType container created, but not used yet."
              << std::endl;

    // 只有当我们尝试调用process()时，才会出现编译错误
    // invalidContainer.process();  // 取消注释这行会导致编译错误

    return 0;
}