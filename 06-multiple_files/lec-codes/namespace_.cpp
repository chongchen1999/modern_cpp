#include <iostream>

// 基本namespace示例
namespace MyNamespace {
    int value = 42;

    void print() {
        std::cout << "Value: " << value << std::endl;
    }

    // 可以嵌套namespace
    namespace Inner {
        void innerFunc() {
            std::cout << "Inner function" << std::endl;
        }
    } // namespace Inner
} // namespace MyNamespace

int main() {
    // 访问namespace中的成员
    std::cout << MyNamespace::value << std::endl; // 输出: 42
    MyNamespace::print();                         // 输出: Value: 42

    // 访问嵌套namespace
    MyNamespace::Inner::innerFunc(); // 输出: Inner function

    // 使用using声明简化访问
    using MyNamespace::value;
    std::cout << value << std::endl; // 输出: 42

    // 使用using namespace引入整个命名空间
    using namespace MyNamespace;
    print(); // 输出: Value: 42

    return 0;
}