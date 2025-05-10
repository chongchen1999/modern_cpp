#include <cassert>
#include <iostream>

// [[nodiscard]] 属性表示函数的返回值不应该被忽略
[[nodiscard]] int compute_important_value() {
    return 42;
}

// [[deprecated]] 属性标记函数为已弃用，并提供替代方案信息
[[deprecated("Use compute_important_value() instead")]] int old_computation() {
    return 24;
}

// [[maybe_unused]] 属性表示变量可能未被使用，避免编译器警告
void process_data([[maybe_unused]] int data) {
// 这个参数可能在某些情况下不被使用
#ifdef DEBUG
    std::cout << "Processing data: " << data << std::endl;
#endif
}

// [[fallthrough]] 属性表示switch语句中的故意贯穿
void handle_value(int value) {
    switch (value) {
        case 1:
            std::cout << "Value is 1" << std::endl;
            [[fallthrough]];  // 故意贯穿到下一个case
        case 2:
            std::cout << "Value is 1 or 2" << std::endl;
            break;
        default:
            std::cout << "Unknown value" << std::endl;
    }
}

// [[noreturn]] 属性表示函数不会返回
[[noreturn]] void fatal_error(const char* msg) {
    std::cerr << "Fatal error: " << msg << std::endl;
    std::terminate();
}

// 类属性示例
class [[nodiscard]] Result {
    int value;

   public:
    Result(int v) : value(v) {}
    int get() const { return value; }
};

Result create_result() {
    return Result(100);
}

int main() {
    // 使用nodiscard函数 - 忽略返回值会触发警告
    // compute_important_value();
    int res = compute_important_value();

    // 使用deprecated函数会触发警告
    // old_computation();

    int x = 10;
    process_data(x);

    handle_value(1);
    handle_value(3);

    // 使用nodiscard类
    // create_result();  // 这会触发警告，因为忽略了返回值
    auto result = create_result();

// 编译器特定属性示例 (GCC/Clang)
#if defined(__GNUC__) || defined(__clang__)
    int y [[gnu::unused]] = 20;  // 等同于[[maybe_unused]]
#endif

// 标准属性可用性检查
#if __has_cpp_attribute(nodiscard) >= 201603L
    std::cout << "[[nodiscard]] is supported" << std::endl;
#endif

    return 0;
}