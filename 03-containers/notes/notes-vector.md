# C++中的Vector介绍

`std::vector`是C++标准模板库(STL)中最常用的容器之一，它是一个动态数组，能够根据需要自动调整大小。

基本特性

1. 动态大小：vector可以根据需要自动扩展或收缩
2. 连续存储：元素在内存中是连续存储的，支持随机访问
3. 自动内存管理：vector会自动处理内存分配和释放

常用操作

创建vector

```cpp
#include <vector>
using namespace std;

vector<int> v1;             // 空vector
vector<int> v2(5);          // 包含5个默认初始化的int
vector<int> v3(5, 10);      // 包含5个值为10的int
vector<int> v4 = {1, 2, 3}; // 初始化列表
vector<int> v5(v4);         // 拷贝构造
```

添加元素

```cpp
v.push_back(10);    // 在末尾添加元素
v.emplace_back(20); // 更高效的添加方式(C++11)
v.insert(v.begin() + 2, 30); // 在指定位置插入元素
```

访问元素

```cpp
int a = v[0];       // 通过下标访问，不检查边界
int b = v.at(1);    // 通过at访问，会检查边界
int c = v.front();  // 第一个元素
int d = v.back();   // 最后一个元素
```

删除元素

```cpp
v.pop_back();       // 删除最后一个元素
v.erase(v.begin()); // 删除指定位置的元素
v.clear();          // 清空所有元素
```

容量操作

```cpp
int size = v.size();      // 当前元素数量
bool empty = v.empty();   // 是否为空
v.resize(10);             // 调整大小
int cap = v.capacity();   // 当前容量
v.reserve(100);           // 预留空间
```

迭代器

```cpp
for(auto it = v.begin(); it != v.end(); ++it) {
    cout << *it << " ";
}

// 或者使用范围for循环(C++11)
for(int num : v) {
    cout << num << " ";
}
```

性能特点

1. 随机访问：O(1)时间复杂度
2. 末尾插入/删除：平均O(1)时间复杂度
3. 中间插入/删除：O(n)时间复杂度
4. 内存分配：当容量不足时，通常会分配当前容量两倍的新空间

适用场景

• 需要频繁随机访问元素

• 主要在末尾添加/删除元素

• 需要动态调整大小的数组


vector是C++中最通用的容器之一，因其灵活性和性能优势而被广泛使用。


# C++ Vector 的底层实现

`std::vector` 是 C++ STL 中最常用的动态数组容器，它的底层实现有几个关键设计点值得深入了解。

1. 基本数据结构

Vector 本质上是一个动态分配的连续数组，包含三个核心指针：

```cpp
template <typename T>
class vector {
private:
    T* _start;      // 指向数组首元素
    T* _finish;     // 指向最后一个元素的下一个位置
    T* _end_of_storage; // 指向分配内存的末尾
};
```

这三个指针的关系：
• `size() = _finish - _start`

• `capacity() = _end_of_storage - _start`


2. 内存管理机制

扩容策略
当插入元素导致 `size() == capacity()` 时，vector 会进行扩容：
1. 分配新内存（通常是当前容量的 2倍，但标准未规定具体倍数）
2. 将旧元素移动或拷贝到新内存
3. 释放旧内存

```cpp
// 伪代码展示扩容过程
void reserve(size_type new_cap) {
    if (new_cap > capacity()) {
        T* new_start = allocator.allocate(new_cap);
        // 移动或拷贝元素到新内存
        for (size_type i = 0; i < size(); ++i) {
            new (&new_start[i]) T(std::move(_start[i]));
            _start[i].~T(); // 销毁旧对象
        }
        allocator.deallocate(_start, capacity());
        _start = new_start;
        _finish = _start + size();
        _end_of_storage = _start + new_cap;
    }
}
```

移动语义优化
C++11 后，vector 会优先使用移动构造函数而非拷贝构造函数，提高性能。

3. 元素访问实现

operator[] 和 at()
```cpp
reference operator[](size_type n) {
    return _start[n]; // 无边界检查
}

reference at(size_type n) {
    if (n >= size()) throw std::out_of_range();
    return _start[n];
}
```

4. 插入删除操作的实现

push_back 实现
```cpp
void push_back(const T& value) {
    if (_finish == _end_of_storage) {
        reserve(size() ? 2 * size() : 1); // 扩容
    }
    new (_finish) T(value); // 原地构造
    ++_finish;
}
```

insert 实现
中间插入需要移动后续元素：
```cpp
iterator insert(iterator pos, const T& value) {
    size_type offset = pos - begin();
    if (_finish == _end_of_storage) {
        reserve(size() ? 2 * size() : 1);
        pos = begin() + offset; // 扩容后迭代器失效，需要重新计算
    }
    std::move_backward(pos, end(), end() + 1); // 向后移动元素
    *pos = value;
    ++_finish;
    return pos;
}
```

5. 迭代器失效规则

以下操作会使迭代器失效：
• 扩容操作（所有迭代器、指针、引用失效）

• 中间插入/删除（插入/删除点之后的迭代器失效）


6. 与数组的性能对比

| 操作 | 普通数组 | vector |
|------|---------|--------|
| 随机访问 | O(1) | O(1) |
| 尾部插入 | 不支持 | 平摊O(1) |
| 中间插入 | 不支持 | O(n) |
| 内存使用 | 固定 | 动态增长 |

7. 实现优化技巧

1. SSO (Small String Optimization)：类似小字符串优化，某些实现会对小vector做特殊处理
2. 移动语义：C++11后显著提高了vector作为函数返回值等场景的性能
3. allocator感知：可以使用自定义分配器控制内存分配行为

vector 的这种实现方式在大多数情况下提供了最佳的性能平衡，这也是它成为C++中最常用容器的原因。