#include <iostream>

template<typename T>
class Base {
public:
    void baseMethod() { std::cout << "Base method\n"; }
    T baseMember;
};

template<typename T>
class Derived : public Base<T> {
public:
    // using Base<T>::baseMethod;    // 方式3（在函数开始处声明）

    void someFunction() {
        // 错误：编译器在第一阶段无法找到baseMethod
        // baseMethod();  // Error!
        
        // 正确的方式：
        this->baseMethod();           // 方式1
        Base<T>::baseMethod();        // 方式2
        
        // 访问成员变量也是如此
        this->baseMember = T{};
    }
};

int main() {
    Derived<int> d;
    d.someFunction();
    return 0;
}