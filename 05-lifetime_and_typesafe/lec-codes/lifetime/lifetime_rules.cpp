#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <new>

// Case 1: 同类型对象复用存储
struct SameType {
    int x;
};

// Case 2: 平凡类型 vs 非平凡类型
struct Trivial {
    int x;
};
struct NonTrivial {
    ~NonTrivial() {}
    int x;
};

// Case 4: unsigned char/std::byte 存储
struct A {
    int val;
};

// Case 5: 类型别名
void print_bytes(int x) {
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&x);
    for (size_t i = 0; i < sizeof(x); ++i)
        std::cout << static_cast<int>(bytes[i]) << " ";
    std::cout << "\n";
}

int main() {
    // Case 1: 同类型复用
    SameType s1{100};
    SameType* ps1 = &s1;
    new (&s1) SameType{200};     // 复用存储
    std::cout << ps1->x << "\n"; // 输出 200（指针仍有效）

    // Case 2: 平凡类型安全复用
    Trivial t1{300};
    new (&t1) Trivial{400};    // 合法
    std::cout << t1.x << "\n"; // 输出 400

    // Case 2: 非平凡类型需手动管理
    NonTrivial nt1{500};
    NonTrivial backup = nt1; // 备份
    new (&nt1) NonTrivial{600};
    nt1.~NonTrivial();             // 析构新对象
    new (&nt1) NonTrivial{backup}; // 恢复原对象

    // Case 3: 禁止复用编译期 const 对象
    const int ro_data = 123;
    // new (&ro_data) int{456}; // 非法：段错误（可能）

    // Case 4: std::byte 存储
    alignas(A) std::byte buffer[sizeof(A)];
    A* pa1 = new (buffer) A{42};
    A* pa2 = std::launder(reinterpret_cast<A*>(buffer)); // 必须 launder
    std::cout << pa2->val << "\n";                       // 输出 42

    // Case 5: 类型别名
    int x = 0x12345678;
    print_bytes(x); // 输出字节序列

    // Case 6: std::launder 的必要性
    alignas(A) char unsafe_buffer[sizeof(A)];
    A* p_unsafe = new (unsafe_buffer) A{99};
    // A* p_bad = reinterpret_cast<A*>(unsafe_buffer); // 未定义行为
    A* p_good = std::launder(reinterpret_cast<A*>(unsafe_buffer));
    std::cout << p_good->val << "\n"; // 输出 99
}