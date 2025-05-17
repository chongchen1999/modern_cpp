#include <iostream>
#include <string>
#include <type_traits>

// ✅ 平凡类型示例
struct TrivialStruct {
    int x;
    double y;
};

struct TrivialWithDefaultConstructor {
    int a;
    float b;
    TrivialWithDefaultConstructor() = default; // 显式默认构造函数
};

struct InnerTrivial {
    int val;
};
struct OuterTrivial {
    InnerTrivial inner;
    float f;
};

// ❌ 非平凡类型示例
struct NonTrivialConstructor {
    int x;
    NonTrivialConstructor() { x = 42; } // 自定义构造函数
};

struct NonTrivialVirtual {
    virtual void foo() {} // 虚函数
};

struct NonTrivialMember {
    std::string s; // std::string 是非平凡的
};

struct NonTrivialDestructor {
    ~NonTrivialDestructor() {} // 自定义析构函数
};

struct NonTrivialReference {
    int& ref; // 引用成员
};

struct BaseNonTrivial {
    virtual ~BaseNonTrivial() {}
};                                            // 虚析构函数
struct DerivedNonTrivial : BaseNonTrivial {}; // 继承导致非平凡

// 辅助函数：打印类型是否平凡
template <typename T>
void checkTrivial(const char* typeName) {
    std::cout << typeName
              << " is trivial: " << (std::is_trivial_v<T> ? "✅" : "❌")
              << std::endl;
}

int main() {
    // ✅ 检测平凡类型
    checkTrivial<int>("int");
    checkTrivial<TrivialStruct>("TrivialStruct");
    checkTrivial<TrivialWithDefaultConstructor>(
        "TrivialWithDefaultConstructor");
    checkTrivial<OuterTrivial>("OuterTrivial");

    // ❌ 检测非平凡类型
    checkTrivial<NonTrivialConstructor>("NonTrivialConstructor");
    checkTrivial<NonTrivialVirtual>("NonTrivialVirtual");
    checkTrivial<NonTrivialMember>("NonTrivialMember");
    checkTrivial<NonTrivialDestructor>("NonTrivialDestructor");
    checkTrivial<NonTrivialReference>("NonTrivialReference");
    checkTrivial<DerivedNonTrivial>("DerivedNonTrivial");

    return 0;
}