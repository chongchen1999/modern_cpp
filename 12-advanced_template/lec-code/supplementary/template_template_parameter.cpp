#include <iostream>
#include <stdexcept> // for std::out_of_range
#include <vector>

template <typename T, template <typename = T, typename = std::allocator<T>>
                      typename Container>
class MyStack {
private:
    Container<> data;

public:
    void push(const T& value);
    void pop();
    T& top();
    const T& top() const;
    bool empty() const;
    size_t size() const;
};

template <typename T, template <typename = T, typename = std::allocator<T>>
                      typename Container>
void MyStack<T, Container>::push(const T& value) {
    data.push_back(value);
}

template <typename T, template <typename = T, typename = std::allocator<T>>
                      typename Container>
void MyStack<T, Container>::pop() {
    if (data.empty()) {
        throw std::out_of_range("Stack is empty");
    }
    data.pop_back();
}

template <typename T, template <typename = T, typename = std::allocator<T>>
                      typename Container>
T& MyStack<T, Container>::top() {
    if (data.empty()) {
        throw std::out_of_range("Stack is empty");
    }
    return data.back();
}

template <typename T, template <typename = T, typename = std::allocator<T>>
                      typename Container>
const T& MyStack<T, Container>::top() const {
    if (data.empty()) {
        throw std::out_of_range("Stack is empty");
    }
    return data.back();
}

template <typename T, template <typename = T, typename = std::allocator<T>>
                      typename Container>
bool MyStack<T, Container>::empty() const {
    return data.empty();
}

template <typename T, template <typename = T, typename = std::allocator<T>>
                      typename Container>
size_t MyStack<T, Container>::size() const {
    return data.size();
}

int main() {
    MyStack<int, std::vector> stack;

    // 测试栈的基本操作
    stack.push(1);
    stack.push(2);
    stack.push(3);

    std::cout << "Top element: " << stack.top() << std::endl; // 应该输出3
    std::cout << "Stack size: " << stack.size() << std::endl; // 应该输出3

    stack.pop();
    std::cout << "Top element after pop: " << stack.top()
              << std::endl; // 应该输出2

    while (!stack.empty()) {
        std::cout << "Popping: " << stack.top() << std::endl;
        stack.pop();
    }

    std::cout << "Stack is now empty: " << (stack.empty() ? "true" : "false")
              << std::endl;

    return 0;
}