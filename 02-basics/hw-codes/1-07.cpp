#include <iostream>
#include <utility> // for std::to_underlying

enum class Permission : unsigned {
    read = 1 << 0,  // 二进制: 001
    write = 1 << 1, // 二进制: 010
    exec = 1 << 2   // 二进制: 100
};

// 重载按位或运算符 |
constexpr Permission operator|(Permission lhs, Permission rhs) {
    return static_cast<Permission>(std::to_underlying(lhs) |
                                   std::to_underlying(rhs));
}

// 重载按位与运算符 &
constexpr Permission operator&(Permission lhs, Permission rhs) {
    return static_cast<Permission>(std::to_underlying(lhs) &
                                   std::to_underlying(rhs));
}

int main() {
    // 测试按位组合
    auto read_write = Permission::read | Permission::write;
    auto all = Permission::read | Permission::write | Permission::exec;

    // 测试按位与
    if ((read_write & Permission::read) == Permission::read) {
        std::cout << "Has read permission\n";
    }

    if ((all & Permission::exec) == Permission::exec) {
        std::cout << "Has exec permission\n";
    }

    return 0;
}