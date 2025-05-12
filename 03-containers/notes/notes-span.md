# Span C++20

`std::span` 是 C++20 引入的一个轻量级的视图类模板，它提供了一种对连续内存块（如数组、`std::vector`、C 风格数组等）进行非拥有式访问的方式。`std::span` 不管理内存，它只是一个指向现有数据的视图，因此使用它不会引入额外的内存开销。

以下是对 `std::span` 的详细介绍：

---

### **1. 特性**
- **非拥有式**：`std::span` 不负责管理底层数据的生命周期，数据的生命周期由原始容器或数组管理。
- **轻量级**：它的实现类似于指针和长度的组合，开销非常小。
- **类型安全**：与裸指针相比，`std::span` 提供了更安全的接口。
- **支持范围操作**：可以与 C++ 的范围 `for` 循环和标准库算法一起使用。
- **多种构造方式**：支持从数组、`std::vector`、`std::array` 等构造。

---

### **2. 使用场景**
- **函数参数传递**：当需要传递数组或容器的视图时，使用 `std::span` 可以避免拷贝数据。
- **统一接口**：通过 `std::span`，可以用统一的方式处理不同类型的连续内存（如数组、`std::vector` 等）。
- **避免裸指针**：提供更安全的替代方案，减少指针操作的错误。

---

### **3. 示例代码**

以下是一些使用 `std::span` 的示例：

#### **3.1 基本用法**
```cpp
#include <iostream>
#include <span>
#include <vector>
#include <array>

void printSpan(std::span<int> s) {
    for (int value : s) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    std::vector<int> vec = {6, 7, 8, 9, 10};
    std::array<int, 5> stdArr = {11, 12, 13, 14, 15};

    // 从 C 风格数组构造 span
    printSpan(arr);

    // 从 std::vector 构造 span
    printSpan(vec);

    // 从 std::array 构造 span
    printSpan(stdArr);

    // 从部分数组构造 span
    printSpan(std::span<int>(arr, 3)); // 只取前 3 个元素

    return 0;
}
```

**输出：**
```
1 2 3 4 5 
6 7 8 9 10 
11 12 13 14 15 
1 2 3 
```

---

#### **3.2 修改底层数据**
`std::span` 提供了对底层数据的直接访问能力，因此可以通过它修改底层数据。

```cpp
#include <iostream>
#include <span>

void modifySpan(std::span<int> s) {
    for (int& value : s) {
        value *= 2; // 将每个元素乘以 2
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};

    modifySpan(arr);

    for (int value : arr) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

**输出：**
```
2 4 6 8 10 
```

---

#### **3.3 空间安全性**
`std::span` 不会越界访问底层数据，任何超出范围的操作都会导致未定义行为。

```cpp
#include <iostream>
#include <span>

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    std::span<int> s(arr, 3); // 只包含前 3 个元素

    for (size_t i = 0; i < s.size(); ++i) {
        std::cout << s[i] << " ";
    }
    std::cout << std::endl;

    // s[3] = 10; // 错误：越界访问，未定义行为

    return 0;
}
```

---

### **4. 常用成员函数**
以下是 `std::span` 的一些常用成员函数：

| 成员函数                  | 说明                                   |
|---------------------------|----------------------------------------|
| `size()`                  | 返回 `span` 中的元素数量               |
| `empty()`                 | 判断 `span` 是否为空                   |
| `operator[]`              | 访问指定索引的元素                     |
| `data()`                  | 返回指向底层数据的指针                 |
| `subspan(offset, count)`  | 返回一个子视图                         |
| `begin()` / `end()`       | 返回迭代器，支持范围 `for` 循环         |

---

### **5. 注意事项**
1. **生命周期管理**：`std::span` 不管理底层数据的生命周期，因此需要确保底层数据在 `span` 的生命周期内有效。
2. **连续内存**：`std::span` 只能用于连续内存块，不能用于链表等非连续容器。
3. **只读视图**：如果需要只读访问，可以使用 `std::span<const T>`。

---

### **6. 总结**
`std::span` 是一个非常实用的工具，它提供了一种安全、高效的方式来操作连续内存块。通过它，可以避免裸指针的使用，同时简化了代码的编写和维护。它特别适合用作函数参数，统一了对数组和容器的处理方式。

如果你正在使用 C++20 或更高版本，建议在合适的场景下使用 `std::span` 来替代裸指针或手动管理的数组视图。