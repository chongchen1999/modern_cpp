#include <iostream>
#include <memory>
#include <vector>

// 基类
class Base {
public:
    int base_data = 10;

    // 虚函数用于演示多态
    virtual void print() const {
        std::cout << "Base: base_data = " << base_data << std::endl;
    }

    // 虚析构函数（避免派生类析构时内存泄漏）
    virtual ~Base() = default;
};

// 派生类
class Derived : public Base {
public:
    int derived_data = 20;

    void print() const override {
        std::cout << "Derived: base_data = " << base_data
                  << ", derived_data = " << derived_data << std::endl;
    }
};

// 函数传参时的切片问题
void passByValue(Base b) {
    std::cout << "Inside passByValue: ";
    b.print(); // 调用基类的print
}

// 通过引用避免切片
void passByRef(const Base& b) {
    std::cout << "Inside passByRef: ";
    b.print(); // 动态调用派生类的print
}

int main() {
    Derived d;

    // 1. 直接赋值导致切片
    Base b = d; // 派生类的derived_data被丢弃
    std::cout << "After slicing assignment: ";
    b.print(); // 输出基类的print

    // 2. 值传递函数参数导致切片
    passByValue(d); // 输出基类的print

    // 3. 引用传递避免切片
    passByRef(d); // 输出派生类的print

    // 4. 使用指针避免切片
    Base* ptr = new Derived();
    std::cout << "Using pointer: ";
    ptr->print(); // 输出派生类的print
    delete ptr;   // 需要虚析构函数！

    // 5. 使用智能指针避免切片和内存泄漏
    std::unique_ptr<Base> smartPtr = std::make_unique<Derived>();
    std::cout << "Using smart pointer: ";
    smartPtr->print(); // 输出派生类的print

    // 6. 容器中存储指针避免切片
    std::vector<std::unique_ptr<Base>> container;
    container.push_back(std::make_unique<Derived>());
    std::cout << "Container element: ";
    container[0]->print(); // 输出派生类的print

    return 0;
}