#include <functional>
#include <iostream>
#include <string>

class Employee {
public:
    std::string name;
    double salary;

    Employee(const std::string& n, double s) : name(n), salary(s) {}

    void printInfo() const {
        std::cout << "Employee: " << name << ", Salary: " << salary
                  << std::endl;
    }

    void raiseSalary(double percentage) { salary *= (1 + percentage / 100.0); }
};

int main() {
    Employee emp("John Doe", 50000.0);

    // 传统成员函数指针方法
    // void (Employee::*printPtr)() const = &Employee::printInfo;
    // void (Employee::*raisePtr)(double) = &Employee::raiseSalary;

    auto printPtr = &Employee::printInfo;
    auto raisePtr = &Employee::raiseSalary;

    std::cout << "=== Traditional method ===" << std::endl;
    (emp.*printPtr)();     // 输出当前信息
    (emp.*raisePtr)(10.0); // 加薪10%
    (emp.*printPtr)();     // 输出更新后的信息

    // 传统成员变量指针方法
    // std::string Employee::*namePtr = &Employee::name;
    // double Employee::*salaryPtr = &Employee::salary;

    auto namePtr = &Employee::name;
    auto salaryPtr = &Employee::salary;

    std::cout << "Name via pointer: " << emp.*namePtr << std::endl;
    emp.*salaryPtr = 60000.0;
    (emp.*printPtr)();

    // 使用 std::invoke
    std::cout << "\n=== std::invoke method ===" << std::endl;
    std::invoke(printPtr, emp);
    std::invoke(raisePtr, emp, 5.0); // 再加薪5%
    std::invoke(printPtr, emp);

    std::cout << "Name via invoke: " << std::invoke(namePtr, emp) << std::endl;
    std::invoke(salaryPtr, emp) = 70000.0;
    std::invoke(printPtr, emp);

    // 使用 std::function 和 std::bind
    std::cout << "\n=== std::function method ===" << std::endl;
    std::function<void()> boundPrint = std::bind(printPtr, &emp);
    std::function<void(double)> boundRaise =
        std::bind(raisePtr, &emp, std::placeholders::_1);

    boundPrint();
    boundRaise(20.0);
    boundPrint();

    return 0;
}