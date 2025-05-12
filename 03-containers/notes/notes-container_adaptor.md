# C++ 中的容器适配器 (Container Adaptors)

容器适配器是C++标准模板库(STL)中提供的一种特殊容器，它们基于现有的序列容器实现，但提供了不同的接口和行为。

主要容器适配器类型

C++标准库提供了三种主要的容器适配器：

1. `std::stack`

特点：
• 后进先出(LIFO)数据结构

• 基于`std::deque`(默认)、`std::vector`或`std::list`实现


主要操作：
```cpp
#include <stack>

std::stack<int> s;
s.push(1);      // 压入元素
s.pop();        // 弹出顶部元素(不返回)
int top = s.top(); // 访问顶部元素
bool empty = s.empty(); // 检查是否为空
size_t size = s.size(); // 获取元素数量
```

2. `std::queue`

特点：
• 先进先出(FIFO)数据结构

• 基于`std::deque`(默认)或`std::list`实现


主要操作：
```cpp
#include <queue>

std::queue<int> q;
q.push(1);      // 在队尾插入元素
q.pop();        // 移除队首元素(不返回)
int front = q.front(); // 访问队首元素
int back = q.back();   // 访问队尾元素
bool empty = q.empty(); // 检查是否为空
size_t size = q.size(); // 获取元素数量
```

3. `std::priority_queue`

特点：
• 元素按优先级排序，最高优先级元素总是在队首

• 默认基于`std::vector`实现，使用堆算法

• 默认比较函数是`std::less<T>`，形成最大堆


主要操作：
```cpp
#include <queue>

std::priority_queue<int> pq;
pq.push(3);     // 插入元素
pq.push(1);
pq.push(4);
int top = pq.top(); // 访问最高优先级元素(4)
pq.pop();       // 移除最高优先级元素
bool empty = pq.empty(); // 检查是否为空
size_t size = pq.size(); // 获取元素数量
```

自定义底层容器

容器适配器允许指定底层容器类型：

```cpp
// 使用vector作为stack的底层容器
std::stack<int, std::vector<int>> s;

// 使用list作为queue的底层容器
std::queue<int, std::list<int>> q;

// 使用deque作为priority_queue的底层容器
std::priority_queue<int, std::deque<int>> pq;
```

注意事项

1. 容器适配器不提供迭代器，不能遍历元素
2. `priority_queue`的插入和删除操作时间复杂度为O(log n)
3. `stack`和`queue`的插入和删除操作通常是O(1)
4. 在调用`top()`、`front()`或`pop()`前应检查容器是否为空

容器适配器提供了简洁的接口来实现常见的数据结构模式，简化了开发过程。