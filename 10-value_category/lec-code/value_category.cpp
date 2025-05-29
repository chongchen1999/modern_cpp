#include <iostream>
#include <type_traits> // for std::is_same_v
#include <utility>     // for std::move

// 辅助函数，打印类型名称
template <typename T>
void printType(const char* name) {
    if (std::is_same_v<T, int>) {
        std::cout << name << " is `int`" << std::endl;
    } else if (std::is_same_v<T, int&>) {
        std::cout << name << " is `int&` (lvalue reference)" << std::endl;
    } else if (std::is_same_v<T, int&&>) {
        std::cout << name << " is `int&&` (rvalue reference)" << std::endl;
    } else {
        std::cout << name << " is unknown type" << std::endl;
    }
}

int getValue() {
    return 42;
} // 返回 prvalue

int& getRef(int& x) {
    return x;
} // 返回 lvalue

int&& getRvalueRef() {
    return 42;
} // 返回 xvalue

int x = 10;
int& get_ref() {
    return x;
}

int main() {
    int a = 10;                                       // `a` 是 lvalue
    std::cout << "Address of a: " << &a << std::endl; // 打印 `a` 的地址

    // --- 1. lvalue 测试 ---
    decltype(a) var1 = a;   // `a` 是 lvalue → `decltype(a)` 是 `int`
    decltype((a)) var2 = a; // `(a)` 是 lvalue → `decltype((a))` 是 `int&`
    printType<decltype(a)>("decltype(a)");
    printType<decltype((a))>("decltype((a))");

    // --- 2. prvalue 测试 ---
    decltype(getValue()) var3 =
        getValue(); // `getValue()` 是 prvalue → `decltype(getValue())` 是 `int`
    printType<decltype(getValue())>("decltype(getValue())");

    // --- 3. xvalue 测试 ---
    decltype(std::move(a)) var4 = std::move(
        a); // `std::move(a)` 是 xvalue → `decltype(std::move(a))` 是 `int&&`
    decltype(getRvalueRef()) var5 =
        getRvalueRef(); // `getRvalueRef()` 是 xvalue →
                        // `decltype(getRvalueRef())` 是 `int&&`
    printType<decltype(std::move(a))>("decltype(std::move(a))");
    printType<decltype(getRvalueRef())>("decltype(getRvalueRef())");

    // --- 4. 综合测试 ---
    int&& rref = std::move(a); // `rref` 是右值引用（绑定到 xvalue）

    std::cout << rref << std::endl; // 打印 rref 的地址

    decltype(rref) var6 = std::move(
        a); // `rref` 是左值（变量名是 lvalue）→ `decltype(rref)` 是 `int&&`
    printType<decltype(rref)>("decltype(rref)");

    // --- 5. 其他测试 ---
    printType<decltype(++a)>("++a"); // `++a` 是 lvalue，因为它是一个左值表达式
    printType<decltype(a++)>("a++");

    auto b = get_ref();           // b 是 int
    decltype(auto) c = get_ref(); // c 是 int&

    std::cout << &get_ref() << std::endl; // 打印 get_ref() 的地址
    printType<decltype(b)>("b");
    printType<decltype(c)>("c");

    return 0;
}