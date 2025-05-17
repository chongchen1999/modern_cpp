#include <cstddef> // for std::byte
#include <iostream>
#include <memory>      // for std::unique_ptr
#include <type_traits> // for std::has_trivial_destructor

// 1. 演示 std::byte 的用法
void demo_byte() {
    std::byte data[4]{};
    data[0] = std::byte{0xAA}; // 用十六进制初始化
    data[1] = std::byte(42);   // 用整数初始化（需要显式转换）

    // 按位运算（std::byte 专为二进制操作设计）
    data[2] = data[0] | std::byte{0x0F};
    data[3] = data[1] & std::byte{0xF0};

    std::cout << "std::byte demo:\n";
    for (const auto& b : data) {
        // 需要强制转换为整数输出（std::byte 没有直接输出流支持）
        std::cout << std::hex << std::to_integer<int>(b) << " ";
    }
    std::cout << "\n\n";
}

// 2. 演示平凡析构函数的不同情况
struct TrivialStruct { // 隐式平凡析构
    int a;
    float b;
};

class TrivialClass { // 显式 default 平凡析构
public:
    ~TrivialClass() = default;
    std::byte data; // 成员也有平凡析构
};

class NonTrivialVirtual { // 虚析构 → 非平凡
public:
    virtual ~NonTrivialVirtual() = default;
};

class NonTrivialMember { // 成员有非平凡析构
public:
    std::unique_ptr<int> ptr;
};

class NonTrivialDefined { // 自定义析构 → 非平凡
public:
    ~NonTrivialDefined() {}
};

// 3. 测试类型是否具有平凡析构
template <typename T>
void check_trivial_dtor(const char* name) {
    std::cout << name << ": "
              << (std::is_trivially_destructible_v<T> ? "Trivial"
                                                      : "Non-trivial")
              << " destructor\n";
}

int main() {
    demo_byte();

    // 检查各种类型的析构函数性质
    check_trivial_dtor<TrivialStruct>("TrivialStruct");
    check_trivial_dtor<TrivialClass>("TrivialClass");
    check_trivial_dtor<NonTrivialVirtual>("NonTrivialVirtual");
    check_trivial_dtor<NonTrivialMember>("NonTrivialMember");
    check_trivial_dtor<NonTrivialDefined>("NonTrivialDefined");

    // 额外验证继承情况
    struct DerivedFromTrivial : TrivialStruct {};
    check_trivial_dtor<DerivedFromTrivial>("DerivedFromTrivial");

    struct DerivedFromNonTrivial : NonTrivialVirtual {};
    check_trivial_dtor<DerivedFromNonTrivial>("DerivedFromNonTrivial");

    return 0;
}