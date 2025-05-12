#include <iostream>

class Base {
public:
    virtual void foo() { std::cout << "Base::foo()" << std::endl; }
    virtual void bar() { std::cout << "Base::bar()" << std::endl; }
    long x = 42;
    virtual void showInfo() {
        std::cout << "Address of vptr of Base: "
                  << reinterpret_cast<void*>(this) << std::endl;
    }
};

class Derived : public Base {
public:
    void foo() override { std::cout << "Derived::foo()" << std::endl; }
    void bar() override { std::cout << "Derived::bar()" << std::endl; }
    long y = 100;
    void showInfo() override {
        std::cout << "Address of vptr of Derived: "
                  << reinterpret_cast<void*>(this) << std::endl;
    }
};

int main() {
    Base* obj = new Derived();
    std::cout << "Address of obj: " << reinterpret_cast<void*>(obj)
              << std::endl;

    std::cout << "Size of obj: " << sizeof(*static_cast<Derived*>(obj))
              << std::endl;

    obj->foo(); // 动态绑定到Derived::foo
    obj->bar(); // 动态绑定到Derived::bar

    // 手动探查内存（仅用于演示，实际中不可移植！）
    void** vptr = *(void***)obj;
    std::cout << "\nVTable contents:" << std::endl;

    std::cout << "  vptr address: " << vptr << std::endl;
    std::cout << "address of x: " << &obj->x << std::endl;
    std::cout << "address of y: " << &((Derived*)obj)->y << std::endl;

    std::cout << "  foo() address: " << vptr[0] << std::endl;
    std::cout << "  bar() address: " << vptr[1] << std::endl;

    obj->showInfo(); // 调用Derived::showInfo

    delete obj;
    return 0;
}