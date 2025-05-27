#include <iostream>
#include <stacktrace>

void foo() {
    auto st = std::stacktrace::current(); // 捕获当前堆栈
    std::cout << "Stack trace:\n" << st << "\n";
}

void bar() {
    foo();
}

int main() {
#ifdef __cpp_lib_stacktrace
    std::cout << "Supported! C++" << __cpp_lib_stacktrace << "\n";
#else
    std::cout << "Not supported!\n";
#endif
    bar();
}