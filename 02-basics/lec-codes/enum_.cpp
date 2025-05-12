#include <iostream>
#include <string>

// 1. 传统枚举示例
enum Color {
    RED,        // 默认值为0
    GREEN = 5,  // 显式设置为5
    BLUE        // 自动递增为6
};

// 2. 强类型枚举示例
enum class TrafficLight {
    RED,     // 0
    YELLOW,  // 1
    GREEN    // 2
};

// 3. 指定底层类型的强类型枚举
enum class SmallEnum : char { A = 'a', B = 'b', C = 'c' };

// 4. 前向声明的枚举
enum class Direction : int;  // 前向声明

void printDirection(Direction dir);

enum class Direction : int { UP, DOWN, LEFT, RIGHT };

// 函数：将Color枚举转换为字符串
std::string colorToString(Color c) {
    switch (c) {
        case RED:
            return "RED";
        case GREEN:
            return "GREEN";
        case BLUE:
            return "BLUE";
        default:
            return "UNKNOWN";
    }
}

// 函数：处理TrafficLight枚举
void handleTrafficLight(TrafficLight light) {
    switch (light) {
        case TrafficLight::RED:
            std::cout << "Stop!" << std::endl;
            break;
        case TrafficLight::YELLOW:
            std::cout << "Slow down!" << std::endl;
            break;
        case TrafficLight::GREEN:
            std::cout << "Go!" << std::endl;
            break;
    }
}

// 函数：打印Direction枚举
void printDirection(Direction dir) {
    switch (dir) {
        case Direction::UP:
            std::cout << "Moving UP" << std::endl;
            break;
        case Direction::DOWN:
            std::cout << "Moving DOWN" << std::endl;
            break;
        case Direction::LEFT:
            std::cout << "Moving LEFT" << std::endl;
            break;
        case Direction::RIGHT:
            std::cout << "Moving RIGHT" << std::endl;
            break;
    }
}

int main() {
    // 1. 传统枚举使用示例
    std::cout << "=== 传统枚举示例 ===" << std::endl;
    Color myColor = GREEN;
    std::cout << "Color: " << colorToString(myColor) << " (value: " << myColor
              << ")" << std::endl;

    // 传统枚举可以隐式转换为整数
    int colorValue = BLUE;
    std::cout << "Blue value: " << colorValue << std::endl;

    // 2. 强类型枚举使用示例
    std::cout << "\n=== 强类型枚举示例 ===" << std::endl;
    TrafficLight light = TrafficLight::GREEN;
    handleTrafficLight(light);

    // 强类型枚举需要显式转换
    std::cout << "Green value: " << static_cast<int>(TrafficLight::GREEN)
              << std::endl;

    // 3. 指定底层类型的枚举
    std::cout << "\n=== 指定底层类型的枚举 ===" << std::endl;
    SmallEnum small = SmallEnum::B;
    std::cout << "SmallEnum B: " << static_cast<char>(small) << std::endl;

    // 4. 前向声明枚举的使用
    std::cout << "\n=== 前向声明枚举示例 ===" << std::endl;
    Direction dir = Direction::RIGHT;
    printDirection(dir);

    // 5. 枚举与switch语句
    std::cout << "\n=== 枚举与switch语句 ===" << std::endl;
    switch (dir) {
        case Direction::UP:
            std::cout << "You're going up!" << std::endl;
            break;
        case Direction::DOWN:
            std::cout << "You're going down!" << std::endl;
            break;
        case Direction::LEFT:
            std::cout << "You're going left!" << std::endl;
            break;
        case Direction::RIGHT:
            std::cout << "You're going right!" << std::endl;
            break;
    }

    return 0;
}