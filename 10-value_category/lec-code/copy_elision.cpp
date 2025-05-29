#include <iostream>
#include <string>

class Widget {
public:
    // 默认构造函数
    Widget() { std::cout << "Default constructor: " << this << "\n"; }

    // 拷贝构造函数
    Widget(const Widget&) { std::cout << "Copy constructor: " << this << "\n"; }

    // 移动构造函数
    Widget(Widget&&) noexcept { std::cout << "Move constructor: " << this << "\n"; }

    // 析构函数
    ~Widget() { std::cout << "Destructor: " << this << "\n"; }

    // 赋值运算符
    Widget& operator=(const Widget&) {
        std::cout << "Copy assignment\n";
        return *this;
    }

    // 移动赋值运算符
    Widget& operator=(Widget&&) noexcept {
        std::cout << "Move assignment\n";
        return *this;
    }
};

// 函数返回临时对象 - 适用RVO
Widget createWidgetRVO() {
    return Widget(); // 直接构造在调用者的内存中
}

// 函数返回命名对象 - 适用NRVO
Widget createWidgetNRVO() {
    Widget w;
    return w; // 可能直接在调用者的内存中构造w
}

// 函数返回参数 - 不适用copy elision
Widget processWidget(Widget w) {
    std::cout << "Processing widget...\n";
    return w; // 这里会发生拷贝或移动
}

int main() {
    std::cout << "=== RVO示例 ===\n";
    Widget w1 = createWidgetRVO(); // 可能完全省略拷贝/移动

    std::cout << "\n=== NRVO示例 ===\n";
    Widget w2 = createWidgetNRVO(); // 可能完全省略拷贝/移动

    std::cout << "\n=== 无优化示例 ===\n";
    Widget w3 = processWidget(Widget()); // 这里可能会有一次移动

    std::cout << "\n=== 临时对象初始化 ===\n";
    Widget w4 = Widget(); // 直接初始化，无拷贝

    std::cout << "\n=== 程序结束 ===\n";
    return 0;
}