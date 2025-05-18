#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

// 1. 基本定义和构造
void demo_construction() {
    std::cout << "=== 1. Variant Construction ===" << std::endl;

    // 定义variant类型，可以存储int, double或string
    using MyVariant = std::variant<int, double, std::string>;

    // 默认构造 - 第一个类型(int)被值初始化(0)
    MyVariant v1;
    std::cout << "Default constructed: " << std::get<int>(v1) << std::endl;

    // 赋值构造 - 根据值类型选择alternative
    MyVariant v2 = 3.14;
    std::cout << "Constructed with double: " << std::get<double>(v2)
              << std::endl;

    // 原地构造 - 直接构造string
    MyVariant v3(std::in_place_type<std::string>, "Hello");
    std::cout << "In-place constructed string: " << std::get<std::string>(v3)
              << std::endl;

    // 通过索引构造 - 索引1对应double
    MyVariant v4(std::in_place_index<1>, 2.718);
    std::cout << "Index-based constructed double: " << std::get<double>(v4)
              << std::endl;

    std::cout << std::endl;
}

// 2. 访问和检查
void demo_access() {
    std::cout << "=== 2. Variant Access ===" << std::endl;

    std::variant<int, double, std::string> v = "Hello World";

    // 获取当前活跃的alternative索引
    std::cout << "Current index: " << v.index() << std::endl;

    // 检查是否持有特定类型
    if (std::holds_alternative<std::string>(v)) {
        std::cout << "Holds a string: " << std::get<std::string>(v)
                  << std::endl;
    }

    // 安全获取指针
    if (auto ptr = std::get_if<double>(&v)) {
        std::cout << "Holds double: " << *ptr << std::endl;
    } else {
        std::cout << "Doesn't hold double" << std::endl;
    }

    // 通过索引访问
    try {
        std::cout << "Element at index 2: " << std::get<2>(v) << std::endl;
    } catch (const std::bad_variant_access& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl;
}

// 3. 访问者模式
void demo_visitor() {
    std::cout << "=== 3. Visitor Pattern ===" << std::endl;
    struct Circle {
        double radius;
    };
    struct Rectangle {
        double width, height;
    };
    struct Triangle {
        double base, height;
    };

    using Shape = std::variant<struct Circle,    // 圆形 {半径}
                               struct Rectangle, // 矩形 {宽, 高}
                               struct Triangle   // 三角形 {底, 高}
                               >;

    std::cout << "size of Shape: " << sizeof(Shape) << std::endl;

    // 定义访问者 - 重载的函数对象
    auto area = [](const auto& shape) -> double {
        using T = std::decay_t<decltype(shape)>;

        if constexpr (std::is_same_v<T, Circle>) {
            return 3.14159 * shape.radius * shape.radius;
        } else if constexpr (std::is_same_v<T, Rectangle>) {
            return shape.width * shape.height;
        } else if constexpr (std::is_same_v<T, Triangle>) {
            return 0.5 * shape.base * shape.height;
        }
        return 0.0;
    };

    // 创建形状集合
    std::vector<Shape> shapes = {Circle{2.0}, Rectangle{3.0, 4.0},
                                 Triangle{5.0, 6.0}};

    // 计算每个形状的面积
    for (const auto& shape : shapes) {
        std::cout << "Area: " << std::visit(area, shape) << std::endl;
    }

    std::cout << std::endl;
}

// 4. 异常状态和monostate
void demo_exception_state() {
    std::cout << "=== 4. Exception State and Monostate ===" << std::endl;

    struct ThrowingType {
        ThrowingType(int) { throw std::runtime_error("Construction failed"); }
    };

    using MyVariant = std::variant<int, ThrowingType, std::string>;

    MyVariant v = 42;

    try {
        // 尝试构造会抛出异常的类型
        v = ThrowingType(1);
    } catch (...) {
        std::cout << "Exception caught during assignment" << std::endl;
    }

    // 检查variant是否处于无效状态
    if (v.valueless_by_exception()) {
        std::cout << "Variant is valueless (index: " << v.index() << ")"
                  << std::endl;
    }

    // 使用monostate表示空状态
    using OptionalInt = std::variant<std::monostate, int>;
    OptionalInt o1;

    if (std::holds_alternative<std::monostate>(o1)) {
        std::cout << "OptionalInt is empty" << std::endl;
    }

    o1 = 42;
    if (std::holds_alternative<int>(o1)) {
        std::cout << "OptionalInt has value: " << std::get<int>(o1)
                  << std::endl;
    }

    std::cout << std::endl;
}

// 5. 其他操作
void demo_other_operations() {
    std::cout << "=== 5. Other Operations ===" << std::endl;

    std::variant<int, std::string> v1 = "Hello";
    std::variant<int, std::string> v2 = 42;

    // emplace操作
    v1.emplace<std::string>("World");
    std::cout << "After emplace: " << std::get<std::string>(v1) << std::endl;

    // 交换
    std::swap(v1, v2);
    std::cout << "After swap: v1=" << std::get<int>(v1)
              << ", v2=" << std::get<std::string>(v2) << std::endl;

    // 比较操作
    std::variant<int, std::string> v3 = 42;
    std::variant<int, std::string> v4 = "Hello";

    std::cout << "v1 == v3: " << (v1 == v3) << std::endl;
    std::cout << "v1 < v4: " << (v1 < v4) << std::endl;

    // 类型信息
    std::cout << "Number of alternatives: "
              << std::variant_size_v<decltype(v1)> << std::endl;
    std::cout << "Type of index 1: "
              << typeid(std::variant_alternative_t<1, decltype(v1)>).name()
              << std::endl;

    std::cout << std::endl;
}

// 6. 实际应用示例 - OpenGL附件模拟
void demo_practical_example() {
    std::cout << "=== 6. Practical Example (OpenGL Attachments) ==="
              << std::endl;

    // 模拟OpenGL描述符
    using GLuint = unsigned int;

    // 附件类型 - 纹理或渲染缓冲区
    struct Texture {
        GLuint id;
    };
    struct RenderBuffer {
        GLuint id;
    };
    using Attachment = std::variant<Texture, RenderBuffer>;

    // 获取描述符的访问者
    auto getDescriptor = [](const auto& attach) -> GLuint { return attach.id; };

    // 创建附件集合
    std::vector<Attachment> attachments = {Texture{1}, RenderBuffer{2},
                                           Texture{3}};

    // 打印所有附件的描述符
    for (const auto& attach : attachments) {
        std::cout << "Attachment descriptor: "
                  << std::visit(getDescriptor, attach) << std::endl;
    }

    std::cout << std::endl;
}

void demo_check_address() {
    std::cout << "=== 7. Check Address ===" << std::endl;

    // 定义variant类型，可以存储int, double或string
    using MyVariant = std::variant<int, double, std::string>;

    std::cout << "Size of Variant is: " << sizeof(MyVariant) << std::endl;

    MyVariant a = 42;
    std::cout << "Address of MyVariant<int>: " << &std::get<int>(a)
              << std::endl;

    a = 3.14;
    std::cout << "Address of MyVariant<double>: " << &std::get<double>(a)
              << std::endl;

    a = std::string("HH");
    std::cout << "Address of MyVariant<double>: " << &std::get<std::string>(a)
              << std::endl;
}

int main() {
    demo_construction();
    demo_access();
    demo_visitor();
    demo_exception_state();
    demo_other_operations();
    demo_practical_example();
    demo_check_address();

    return 0;
}