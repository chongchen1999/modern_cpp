#include <iostream>
#include <source_location>

void log(const std::string& message,
         const std::source_location& loc = std::source_location::current()) {
    std::cout << "File: " << loc.file_name() << " (" << loc.line() << ":"
              << loc.column() << ")"
              << "\nFunction: " << loc.function_name()
              << "\nMessage: " << message << "\n\n";
}

void foo() {
    log("Hello from foo!"); // 自动捕获调用位置
}

int main() {
    log("Hello from main!");
    foo();
}