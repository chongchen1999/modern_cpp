#include <iostream>

enum class Color { red, blue, green };

int main() {
    using enum Color; // 避免重复写 Color::

    Color color = Color::red; // 可以改为 blue 或 green 测试

    switch (color) {
    case red:
    case green:
        std::cout << "Hello" << std::endl;
        break;
    case blue:
        std::cout << "World" << std::endl;
        break;
        // 不需要 default，因为枚举已经覆盖所有情况
    }

    // 使用 [[fallthrough]] 的示例（题目未要求，但补充说明）
    switch (color) {
    case red:
        std::cout << "Red path" << std::endl;
        [[fallthrough]]; // 明确告知编译器这是故意的 fallthrough
    case green:
        std::cout << "Hello" << std::endl;
        break;
    case blue:
        std::cout << "World" << std::endl;
        break;
    }

    return 0;
}