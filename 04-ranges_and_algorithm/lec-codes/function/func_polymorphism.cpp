#include <functional>
#include <iostream>

class Shape {
public:
    virtual void draw() const { std::cout << "Drawing a shape" << std::endl; }
    virtual ~Shape() = default;
};

class Circle : public Shape {
public:
    void draw() const override { std::cout << "Drawing a circle" << std::endl; }
};

int main() {
    Circle circle;
    Shape shape;

    // 存储成员函数的 std::function
    std::function<void(const Shape&)> drawFunc = &Shape::draw;

    drawFunc(shape);  // 输出: Drawing a shape
    drawFunc(circle); // 输出: Drawing a circle (多态调用)

    return 0;
}