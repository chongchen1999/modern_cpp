#include <cstdlib>
#include <exception>
#include <iostream>

class Resource {
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource released\n"; }
};

void test_abort() {
    Resource res;
    std::abort(); // 析构函数不会被调用！
}

void test_terminate() {
    Resource res;
    throw 42; // 未捕获异常，触发 terminate()
}

int main() {
    test_abort();   // 输出: "Resource acquired" [无析构调用]
    test_terminate(); // 输出: "Resource acquired" [析构可能不调用]
    return 0;
}