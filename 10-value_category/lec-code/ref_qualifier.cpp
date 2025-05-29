#include <iostream>
#include <string>
#include <utility>

class TextHolder {
private:
    std::string text;

public:
    // 构造函数
    TextHolder(const std::string& s) : text(s) {}

    // 普通成员函数
    void print() const { std::cout << "Text: " << text << std::endl; }

    // 左值限定版本
    void modify() & {
        text += " (modified by lvalue)";
        std::cout << "Modified by lvalue: " << text << std::endl;
    }

    // 右值限定版本
    void modify() && {
        text += " (modified by rvalue)";
        std::cout << "Modified by rvalue: " << text << std::endl;
    }

    // 获取文本的左值限定版本
    const std::string& get() const& {
        std::cout << "Getting text from lvalue" << std::endl;
        return text;
    }

    // 获取文本的右值限定版本
    std::string get() && {
        std::cout << "Getting text from rvalue" << std::endl;
        return std::move(text); // 可以安全地移动
    }
};

// 测试函数
void testReferenceQualifiers() {
    std::cout << "=== Testing lvalue ===" << std::endl;
    TextHolder lvalueObj("Hello");
    lvalueObj.modify();        // 调用左值版本
    auto s1 = lvalueObj.get(); // 调用左值版本

    std::cout << "\n=== Testing rvalue ===" << std::endl;
    auto s2 = TextHolder("World").get(); // 调用右值版本
    TextHolder("Temp").modify();         // 调用右值版本

    std::cout << "\n=== Testing combined ===" << std::endl;
    TextHolder combined("Combined");
    std::move(combined).modify(); // 强制调用右值版本
}

int main() {
    testReferenceQualifiers();
    return 0;
}