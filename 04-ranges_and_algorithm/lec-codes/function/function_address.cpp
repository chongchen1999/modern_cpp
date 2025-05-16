#include <iostream>
#include <iomanip>

class MyClass {
public:
    void foo(int x) { 
        std::cout << "foo: " << x << std::endl; 
    }
    int bar(double d) { 
        std::cout << "bar: " << d << std::endl; 
        return 0; 
    }
};

int main() {
    // 定义成员函数指针
    void (MyClass::*funcPtr)(int) = &MyClass::foo;
    int (MyClass::*funcPtr2)(double) = &MyClass::bar;

    // 输出地址（需转换为void*，但行为是实现定义的）
    std::cout << "Address of foo: " << reinterpret_cast<void*>(&MyClass::foo) << std::endl;
    std::cout << "Address of bar: " << reinterpret_cast<void*>(&MyClass::bar) << std::endl;

    // 通过对象调用
    MyClass obj;
    (obj.*funcPtr)(42);       // 调用 foo(42)
    (obj.*funcPtr2)(3.14);    // 调用 bar(3.14)

    return 0;
}