#include <array>
#include <iostream>

// 1. 基本NTTP示例 - 整型参数
template <int N>
class FixedArray {
public:
    int data[N]; // 使用NTTP指定数组大小

    void printSize() const {
        std::cout << "FixedArray size: " << N << std::endl;
    }
};

// 2. NTTP可以是编译时常量表达式
constexpr int getDefaultSize() {
    return 10;
}

template <int Size = getDefaultSize()>
class DynamicArray {
public:
    void printSize() const {
        std::cout << "DynamicArray default size: " << Size << std::endl;
    }
};

// 3. NTTP可以是枚举值
enum class Color { Red, Green, Blue };

template <Color C>
class ColoredWidget {
public:
    void printColor() const {
        std::cout << "Widget color: ";
        switch (C) {
            case Color::Red:
                std::cout << "Red";
                break;
            case Color::Green:
                std::cout << "Green";
                break;
            case Color::Blue:
                std::cout << "Blue";
                break;
        }
        std::cout << std::endl;
    }
};

// 4. C++20起，NTTP可以是浮点数
template <double Value>
class FloatingPointExample {
public:
    void printValue() const {
        std::cout << "Floating point value: " << Value << std::endl;
    }
};

// 5. NTTP可以是对象指针（C++17起）
struct MyType {
    const char* name;
};

template <MyType* ptr>
class PointerExample {
public:
    void printName() const {
        std::cout << "Name from pointer: " << ptr->name << std::endl;
    }
};

// 全局对象用于指针NTTP
MyType globalObj{"Global Object"};

int main() {
    // 1. 使用整型NTTP
    FixedArray<5> arr1;
    arr1.printSize();

    // 2. 使用默认NTTP
    DynamicArray<> arr2;
    arr2.printSize();

    // 3. 使用枚举NTTP
    ColoredWidget<Color::Green> widget;
    widget.printColor();

    // 4. 使用浮点数NTTP (C++20)
    FloatingPointExample<3.14159> fp;
    fp.printValue();

    // 5. 使用对象指针NTTP (C++17)
    PointerExample<&globalObj> ptrEx;
    ptrEx.printName();

    // 实际应用示例 - std::array使用NTTP指定大小
    std::array<int, 5> stdArr;
    std::cout << "std::array size: " << stdArr.size() << std::endl;

    return 0;
}