#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

class BankAccount {
private:
    int balance;
    std::string name;

public:
    BankAccount(int initialBalance, const std::string& accountName)
        : balance(initialBalance), name(accountName) {}

    // 1. No-throw guarantee (标记为 noexcept)
    void setNameNoThrow(const std::string& newName) noexcept {
        name = newName; // std::string 的赋值通常不会抛出异常
    }

    // 2. Strong exception guarantee
    void deposit(int amount) {
        if (amount < 0)
            throw std::invalid_argument("Amount cannot be negative");

        int oldBalance = balance; // 保存旧状态
        balance +=
            amount; // 修改状态（可能抛出异常？实际上基本类型操作不会抛出）

        // 如果 balance 是复杂类型，此处可能抛出异常，
        // 但因为是 int，所以强保证自动满足
    }

    // 3. Basic exception guarantee
    void withdraw(int amount) {
        if (amount < 0)
            throw std::invalid_argument("Amount cannot be negative");
        if (amount > balance)
            throw std::runtime_error("Insufficient funds");

        balance -= amount; // 基本操作，不会抛出
        // 假设此处可能调用其他可能抛出异常的操作（如日志记录）
        // 但即使抛出异常，balance 已被修改，但程序状态仍有效（无泄漏）
    }

    // 4. No guarantee (危险操作)
    void riskyTransfer(BankAccount& other, int amount) {
        withdraw(amount);      // 可能抛出异常
        other.deposit(amount); // 可能抛出异常
        // 如果 deposit 抛出异常，钱已从当前账户扣除但未转入目标账户！
    }

    // 提供强保证的 transfer（通过 "copy-and-swap" 技术）
    void safeTransfer(BankAccount& other, int amount) {
        BankAccount thisCopy = *this;  // 拷贝当前状态
        BankAccount otherCopy = other; // 拷贝目标状态

        thisCopy.withdraw(amount); // 操作副本
        otherCopy.deposit(amount); // 操作副本

        // 如果以上操作均成功，交换新状态（no-throw）
        *this = std::move(thisCopy);  // noexcept（移动赋值）
        other = std::move(otherCopy); // noexcept
    }

    void printBalance() const {
        std::cout << name << ": balance = " << balance << std::endl;
    }
};

int main() {
    try {
        BankAccount alice(100, "Alice");
        BankAccount bob(50, "Bob");

        // 演示 no-throw 保证
        alice.setNameNoThrow("Alice Smith"); // 不会抛出异常
        alice.printBalance();

        // 演示强保证
        alice.deposit(50); // 成功
        alice.printBalance();

        alice.deposit(-10); // 抛出异常，但 alice 的状态回滚到调用前
        alice.printBalance();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    try {
        BankAccount alice(100, "Alice");
        BankAccount bob(50, "Bob");

        // 演示基本保证
        alice.withdraw(30); // 成功
        alice.printBalance();

        alice.withdraw(200); // 抛出异常，但程序状态仍有效（无泄漏）
        alice.printBalance();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    try {
        BankAccount alice(100, "Alice");
        BankAccount bob(50, "Bob");

        // 演示无保证的危险操作
        alice.riskyTransfer(bob, 70); // 第一次成功
        alice.printBalance();
        bob.printBalance();

        alice.riskyTransfer(bob, 70); // 第二次会抛出异常（余额不足）
        // 但若 deposit 抛出异常，钱会消失！
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        // 此处 alice 和 bob 的状态可能不一致
    }

    try {
        BankAccount alice(100, "Alice");
        BankAccount bob(50, "Bob");

        // 演示强保证的 transfer
        alice.safeTransfer(bob, 70); // 成功
        alice.printBalance();
        bob.printBalance();

        alice.safeTransfer(bob, 70); // 失败，但状态完全回滚
        alice.printBalance();
        bob.printBalance();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}