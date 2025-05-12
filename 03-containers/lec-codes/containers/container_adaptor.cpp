#include <functional> // 用于 std::greater
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <list>

// 函数声明
void demonstrateStack();
void demonstrateQueue();
void demonstratePriorityQueue();

int main() {
    std::cout << "=== C++ 容器适配器演示程序 ===" << std::endl;

    std::cout << "\n[1] 演示 stack (后进先出 LIFO)" << std::endl;
    demonstrateStack();

    std::cout << "\n[2] 演示 queue (先进先出 FIFO)" << std::endl;
    demonstrateQueue();

    std::cout << "\n[3] 演示 priority_queue (优先级队列)" << std::endl;
    demonstratePriorityQueue();

    return 0;
}

// 演示 stack 的使用
void demonstrateStack() {
    // 创建一个整数栈，默认基于deque
    std::stack<int> s;

    // 压入元素
    s.push(10);
    s.push(20);
    s.push(30);

    std::cout << "栈大小: " << s.size() << std::endl;
    std::cout << "栈顶元素: " << s.top() << std::endl;

    // 弹出元素
    std::cout << "弹出元素: ";
    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;

    // 使用vector作为底层容器的stack
    std::stack<int, std::vector<int>> s2;
    s2.push(100);
    s2.push(200);
    std::cout << "基于vector的栈顶元素: " << s2.top() << std::endl;
}

// 演示 queue 的使用
void demonstrateQueue() {
    // 创建一个整数队列，默认基于deque
    std::queue<int> q;

    // 入队
    q.push(10);
    q.push(20);
    q.push(30);

    std::cout << "队列大小: " << q.size() << std::endl;
    std::cout << "队首元素: " << q.front() << std::endl;
    std::cout << "队尾元素: " << q.back() << std::endl;

    // 出队
    std::cout << "出队顺序: ";
    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << std::endl;

    // 使用list作为底层容器的queue
    std::queue<int, std::list<int>> q2;
    q2.push(100);
    q2.push(200);
    std::cout << "基于list的队首元素: " << q2.front() << std::endl;
}

// 演示 priority_queue 的使用
void demonstratePriorityQueue() {
    // 创建一个最大堆（默认）
    std::priority_queue<int> maxHeap;

    maxHeap.push(30);
    maxHeap.push(10);
    maxHeap.push(50);
    maxHeap.push(20);

    std::cout << "最大堆大小: " << maxHeap.size() << std::endl;
    std::cout << "最大堆顶元素: " << maxHeap.top() << std::endl;

    std::cout << "弹出顺序: ";
    while (!maxHeap.empty()) {
        std::cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    std::cout << std::endl;

    // 创建一个最小堆（使用std::greater）
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

    minHeap.push(30);
    minHeap.push(10);
    minHeap.push(50);
    minHeap.push(20);

    std::cout << "最小堆顶元素: " << minHeap.top() << std::endl;
    std::cout << "弹出顺序: ";
    while (!minHeap.empty()) {
        std::cout << minHeap.top() << " ";
        minHeap.pop();
    }
    std::cout << std::endl;

    // 使用自定义比较函数的priority_queue
    auto cmp = [](int left, int right) { return (left % 10) < (right % 10); };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> customHeap(cmp);

    customHeap.push(31);
    customHeap.push(12);
    customHeap.push(53);
    customHeap.push(24);

    std::cout << "自定义比较的堆顶元素: " << customHeap.top() << std::endl;
}