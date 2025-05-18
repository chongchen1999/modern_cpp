#include <iostream>

// 纯虚基类（接口）
class Interface {
public:
    virtual void pureVirtualFunction() = 0; // 纯虚函数
    virtual ~Interface() {}                 // 虚析构函数
};

// 普通基类
class Base {
public:
    virtual void baseFunction() {
        std::cout << "Base::baseFunction()" << std::endl;
    }

    virtual ~Base() { std::cout << "Base::~Base()" << std::endl; }
};

// 另一个基类，将被虚继承
class VirtualBase {
public:
    virtual void virtualBaseFunction() {
        std::cout << "VirtualBase::virtualBaseFunction()" << std::endl;
    }

    virtual ~VirtualBase() {
        std::cout << "VirtualBase::~VirtualBase()" << std::endl;
    }
};

// 多重继承类，同时继承Base和Interface，并虚继承VirtualBase
class Derived : public Base, public Interface, virtual public VirtualBase {
public:
    // 实现纯虚函数
    void pureVirtualFunction() override {
        std::cout << "Derived::pureVirtualFunction()" << std::endl;
    }

    // 重写基类虚函数
    void baseFunction() override {
        std::cout << "Derived::baseFunction()" << std::endl;
    }

    // 添加新的虚函数
    virtual void derivedFunction() {
        std::cout << "Derived::derivedFunction()" << std::endl;
    }

    ~Derived() override { std::cout << "Derived::~Derived()" << std::endl; }
};

int main() {
    Derived d;

    // 通过不同基类指针调用虚函数
    Base* basePtr = &d;
    Interface* interfacePtr = &d;
    VirtualBase* virtualBasePtr = &d;

    std::cout << "Calling functions through Base pointer:" << std::endl;
    basePtr->baseFunction();

    std::cout << "\nCalling functions through Interface pointer:" << std::endl;
    interfacePtr->pureVirtualFunction();

    std::cout << "\nCalling functions through VirtualBase pointer:"
              << std::endl;
    virtualBasePtr->virtualBaseFunction();

    std::cout << "\nCalling functions through Derived object:" << std::endl;
    d.derivedFunction();

    return 0;
}