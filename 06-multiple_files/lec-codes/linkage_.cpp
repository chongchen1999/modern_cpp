// File: linkage_example.cpp

#include <iostream>

// 外部链接 - 可以在其他文件中通过extern声明访问
extern int global_var;  // 声明，定义在其他文件中
int another_global = 20;  // 定义，具有外部链接

// 内部链接 - 只能在当前文件中访问
static int internal_var = 30;
namespace {  // 匿名命名空间，内部链接
    int anonymous_var = 40;
}

// 外部链接函数
void external_func() {
    std::cout << "External linkage function\n";
}

// 内部链接函数
static void internal_func() {
    std::cout << "Internal linkage function\n";
}

// 无链接的例子
void example_function(int param) {  // param无链接
    int local_var = 50;  // 局部变量，无链接
    static int static_local = 60;  // 静态局部变量，无链接但生命周期延长
    
    std::cout << "Local var: " << local_var << std::endl;
    static_local++;
    std::cout << "Static local var: " << static_local << std::endl;
}

class MyClass {  // 类名有外部链接
public:
    static int class_var;  // 静态成员变量，外部链接
    void member_func() {   // 成员函数，外部链接
        int member_local = 70;  // 无链接
    }
};

int MyClass::class_var = 80;  // 静态成员变量定义

int main() {
    std::cout << "External linkage variables:\n";
    std::cout << "global_var: " << global_var << std::endl;  // 定义在另一个文件
    std::cout << "another_global: " << another_global << std::endl;
    
    std::cout << "\nInternal linkage variables:\n";
    std::cout << "internal_var: " << internal_var << std::endl;
    std::cout << "anonymous_var: " << anonymous_var << std::endl;
    
    std::cout << "\nFunctions:\n";
    external_func();
    internal_func();
    
    std::cout << "\nNo linkage examples:\n";
    example_function(0);
    example_function(0);
    
    std::cout << "\nClass static member:\n";
    std::cout << "MyClass::class_var: " << MyClass::class_var << std::endl;
    
    return 0;
}