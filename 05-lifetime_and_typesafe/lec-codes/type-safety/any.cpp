#include <any>
#include <iostream>
#include <string>
#include <typeinfo>
#include <utility>

// 1. 基本使用和存储任何对象
void demo_basic_usage() {
    std::cout << "\n=== 基本使用和存储任何对象 ===\n";

    std::any a = 42;
    std::cout << "存储int: " << std::any_cast<int>(a) << std::endl;

    a = std::string("Hello");
    std::cout << "存储string: " << std::any_cast<std::string>(a) << std::endl;

    a = 3.14;
    std::cout << "存储double: " << std::any_cast<double>(a) << std::endl;
}

// 2. 需要复制构造函数
void demo_copy_requirement() {
    std::cout << "\n=== 需要复制构造函数 ===\n";

    struct Copyable {
        Copyable() = default;
        Copyable(const Copyable&) { std::cout << "Copy ctor called\n"; }
    };

    struct NonCopyable {
        NonCopyable() = default;
        NonCopyable(const NonCopyable&) = delete;
    };

    Copyable c;
    std::any a1 = c; // 正常，有复制构造函数

    // 下面的代码会编译错误，因为没有复制构造函数
    // NonCopyable nc;
    // std::any a2 = nc;

    std::cout << "只有具有复制构造函数的类型才能存储在std::any中\n";
}

// 3. 类型退化
void demo_type_decay() {
    std::cout << "\n=== 类型退化 ===\n";

    int arr[3] = {1, 2, 3};
    std::any a = arr;

    // 数组类型会退化为指针
    std::cout << "数组类型存储后会退化为指针: " << (a.type() == typeid(int*))
              << std::endl;
}

// 4. 默认构造和重置
void demo_default_and_reset() {
    std::cout << "\n=== 默认构造和重置 ===\n";

    std::any a;
    std::cout << "默认构造后是否有值: " << a.has_value() << std::endl;

    a = 42;
    std::cout << "赋值后是否有值: " << a.has_value() << std::endl;

    a.reset();
    std::cout << "reset()后是否有值: " << a.has_value() << std::endl;
}

// 5. 检查是否有值
void demo_has_value() {
    std::cout << "\n=== 检查是否有值 ===\n";

    std::any a;
    std::cout << "空any的has_value(): " << a.has_value() << std::endl;

    a = 42;
    std::cout << "有值的any的has_value(): " << a.has_value() << std::endl;
}

// 6. 原位构造
void demo_in_place_construction() {
    std::cout << "\n=== 原位构造 ===\n";

    // 使用in_place_t直接构造对象，避免额外的复制/移动
    std::any a{std::in_place_type<std::string>, 5, 'A'};
    std::cout << "原位构造的string: " << std::any_cast<std::string>(a)
              << std::endl;

    struct Point {
        int x, y;
        Point(int x, int y) : x(x), y(y) {}
    };

    std::any b(std::in_place_type<Point>, 10, 20);
    auto p = std::any_cast<Point>(b);
    std::cout << "原位构造的Point: (" << p.x << ", " << p.y << ")\n";
}

// 7. 精确类型转换
void demo_exact_type_casting() {
    std::cout << "\n=== 精确类型转换 ===\n";

    std::any a = 100LL; // long long

    try {
        // 错误的转换，类型不匹配
        std::cout << "尝试转换为int: ";
        std::cout << std::any_cast<int>(a) << std::endl;
    } catch (const std::bad_any_cast& e) {
        std::cout << "捕获异常: " << e.what() << std::endl;
    }

    // 正确的转换方式
    long long ll = std::any_cast<long long>(a);
    std::cout << "正确转换后的值: " << ll << std::endl;

    // 使用指针转换
    auto ptr = std::any_cast<long long>(&a);
    std::cout << "指针转换的值: " << (ptr ? *ptr : 0) << std::endl;
}

// 8. 小缓冲区优化(SBO)
void demo_sbo() {
    std::cout << "\n=== 小缓冲区优化(SBO) ===\n";

    std::cout << "std::any的大小: " << sizeof(std::any) << " bytes\n";

    // 小对象可能存储在栈上
    std::any small = 42;
    std::cout << "小对象(42)存储后: " << small.has_value() << std::endl;

    // 大对象可能存储在堆上
    struct Large {
        char data[64];
    };
    std::any large = Large{};
    std::cout << "大对象存储后: " << large.has_value() << std::endl;
}

// 9. 辅助函数
void demo_helper_functions() {
    std::cout << "\n=== 辅助函数 ===\n";

    // 交换
    std::any a = 42;
    std::any b = std::string("Hello");
    std::cout << "交换前: a=" << std::any_cast<int>(a)
              << ", b=" << std::any_cast<std::string>(b) << std::endl;
    a.swap(b);
    std::cout << "交换后: a=" << std::any_cast<std::string>(a)
              << ", b=" << std::any_cast<int>(b) << std::endl;

    // 类型信息
    std::cout << "a的类型: " << a.type().name() << std::endl;

    // emplace
    a.emplace<float>(3.14f);
    std::cout << "emplace后的值: " << std::any_cast<float>(a) << std::endl;

    // make_any
    auto c = std::make_any<std::string>("World");
    std::cout << "make_any创建的值: " << std::any_cast<std::string>(c)
              << std::endl;
}

int main() {
    demo_basic_usage();
    demo_copy_requirement();
    demo_type_decay();
    demo_default_and_reset();
    demo_has_value();
    demo_in_place_construction();
    demo_exact_type_casting();
    demo_sbo();
    demo_helper_functions();

    return 0;
}