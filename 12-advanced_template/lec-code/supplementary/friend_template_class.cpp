#include <iostream>

// 前向声明
template <typename>
class Storage;
template <typename T>
void display(const Storage<T>&);

template <typename T>
class Storage {
private:
    T value;

public:
    Storage(T val) : value(val) {}

    // 声明特定实例化的display函数为友元
    friend void display<>(const Storage<T>&);
};

template <typename T>
void display(const Storage<T>& storage) {
    std::cout << storage.value << std::endl;
}

int main() {
    Storage<int> s1(42);
    Storage<double> s2(3.14);

    display<int>(s1); // 输出: 42
    display(s2); // 输出: 3.14

    return 0;
}