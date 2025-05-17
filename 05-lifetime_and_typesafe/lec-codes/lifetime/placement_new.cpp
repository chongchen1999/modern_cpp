#include <iostream>
#include <new>

class MyClass {
public:
    MyClass(int val) : value(val) {
        std::cout << "Constructed. value=" << value << std::endl;
    }
    ~MyClass() { std::cout << "Destructed." << std::endl; }

private:
    int value;
};

int main() {
    // 1. 预先分配内存（对齐通过 `alignas` 保证）
    alignas(MyClass) char buffer[sizeof(MyClass)];

    // 2. 使用 placement new 构造对象
    MyClass* obj = new (buffer) MyClass(42);

    // 3. 显式调用析构函数
    obj->~MyClass();

    // 注意：buffer 的内存需自行管理（栈数组在此自动释放）
    return 0;
}