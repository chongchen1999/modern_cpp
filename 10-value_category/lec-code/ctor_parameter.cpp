#include <iostream>
#include <string>
#include <utility>

// 用于跟踪构造/移动/析构调用
struct Tracer {
    std::string name;
    Tracer(const std::string& n) : name(n) {
        std::cout << name << ": copy constructed\n";
    }

    Tracer(const Tracer& other) : name(other.name) {
        std::cout << name << ": copy constructed from lvalue\n";
    }

    Tracer(Tracer&& other) : name(std::move(other.name)) {
        std::cout << name << ": move constructed\n";
    }
    ~Tracer() { std::cout << name << ": destroyed\n"; }
};

// Person 类，测试不同参数传递方式
class Person {
    Tracer name;

public:
    // 1. 值传递（by value）
    Person(Tracer init_name) : name(std::move(init_name)) {
        std::cout << "Value version called\n";
    }

    // // 3. 常量左值引用（const&）
    // Person(const Tracer& init_name) : name(init_name) {
    //     std::cout << "Const Lvalue ref version called\n";
    // }

    // // 4. 右值引用（&&）
    // Person(Tracer&& init_name) : name(std::move(init_name)) {
    //     std::cout << "Rvalue ref version called\n";
    // }
};

int main() {
    std::cout << "===== Testing lvalue (s1) =====\n";
    Tracer s1("Alice");
    Person p1(s1); // 调用哪个构造函数？

    std::cout << "\n===== Testing xvalue (std::move(s2)) =====\n";
    Tracer s2("Bob");
    Person p2(std::move(s2)); // 调用哪个构造函数？

    std::cout << "\n===== Testing prvalue (temporary) =====\n";
    Person p3(Tracer("Charlie")); // 调用哪个构造函数？

    std::cout << "\n===== Program ends =====\n";
}