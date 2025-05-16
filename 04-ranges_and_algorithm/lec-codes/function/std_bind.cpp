#include <functional>
#include <iostream>
#include <memory>

using namespace std::placeholders; // 引入占位符 _1, _2, ...

// 示例1: 绑定普通函数
void print(int a, int b, int c) {
    std::cout << "print: " << a << ", " << b << ", " << c << std::endl;
}

// 示例2: 绑定成员函数
struct Foo {
    void print(int x, int y) {
        std::cout << "Foo::print: " << x << ", " << y << std::endl;
    }
    static void static_print(int x, int y) {
        std::cout << "Foo::static_print: " << x << ", " << y << std::endl;
    }
};

// 示例3: 绑定函数对象
struct Multiply {
    int operator()(int a, int b) const {
        std::cout << "Multiply: " << a << " * " << b << " = ";
        return a * b;
    }
};

// 示例4: 绑定引用参数
void increment(int& x) {
    x++;
    std::cout << "increment to: " << x << std::endl;
}

// 示例5: 嵌套bind
void print_sum(int a, int b, int c) {
    std::cout << "print_sum: " << a << " + " << b << " + " << c << " = "
              << (a + b + c) << std::endl;
}

// 示例6: 绑定到智能指针
struct Bar {
    void foo(int x) { std::cout << "Bar::foo: " << x << std::endl; }
};

int main() {
    std::cout << "=== 示例1: 绑定普通函数 ===" << std::endl;
    {
        // 绑定第一个参数为10，其余使用占位符
        auto f1 = std::bind(&print, 10, _1, _2);
        f1(20, 30); // 输出: 10, 20, 30

        // 重新排序参数
        auto f2 = std::bind(&print, _3, _1, _2);
        f2(1, 2, 3); // 输出: 3, 1, 2
    }

    std::cout << "\n=== 示例2: 绑定成员函数 ===" << std::endl;
    {
        Foo foo;
        // 绑定成员函数需要传递对象指针或引用作为第一个参数
        auto f = std::bind(&Foo::print, &foo, _1, 42);
        f(10); // 输出: 10, 42

        auto f1 = std::bind(Foo::static_print, _1, 42);
        f1(10); // 输出: 10, 42
    }

    std::cout << "\n=== 示例3: 绑定函数对象 ===" << std::endl;
    {
        Multiply mult;
        auto f = std::bind(mult, _1, 5);
        std::cout << f(10) << std::endl; // 输出: 50
    }

    std::cout << "\n=== 示例4: 绑定引用参数 ===" << std::endl;
    {
        int x = 0;
        auto f = std::bind(increment, std::ref(x));
        f();
        std::cout << "Final value: " << x << std::endl; // 输出: 1
    }

    std::cout << "\n=== 示例5: 嵌套bind ===" << std::endl;
    {
        auto f =
            std::bind(print_sum, std::bind(std::plus<int>(), _1, 10), _2, 100);
        f(5, 20); // 输出: 15 + 20 + 100 = 135
    }

    std::cout << "\n=== 示例6: 绑定到智能指针 ===" << std::endl;
    {
        auto ptr = std::make_shared<Bar>();
        auto f = std::bind(&Bar::foo, ptr, _1);
        f(42); // 输出: 42
    }

    return 0;
}