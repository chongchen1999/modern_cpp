# Ranges、Views 和 Range Adaptors 在 C++ 中的介绍

好的，我们来介绍一下 C++ 中在 C++20 引入的 Ranges（范围）、Views（视图）和 Range Adaptors（范围适配器）。它们是 C++ 标准库中用于处理序列数据的一组强大工具，旨在提供一种更函数式、更易读、更易组合的方式来操作数据集合。

**1. Range (范围)**

在 C++ 中，**Range** 是一个核心概念，它抽象了传统 C++03/11/14/17 中使用一对迭代器 `[begin, end)` 来表示一个序列的方式。简单来说，一个 Range 就是任何可以被迭代的东西，它提供了获取其起始迭代器 (`begin()`) 和结束标志 (`end()`) 的方法。

Ranges 的目标是让算法能够直接作用于容器或其他可迭代对象，而不再强制用户显式地传递一对迭代器。这使得代码更加简洁和直观。

任何满足 `std::ranges::range` concept 的类型都可以被视为一个 Range。这通常意味着它需要提供 `ranges::begin()` 和 `ranges::end()` 函数（可以通过成员函数或非成员 ADL (Argument-Dependent Lookup) 函数找到）。

例如，`std::vector`, `std::list`, `std::array` 等标准容器都是 Range。一个原始数组 `int arr[]` 也是 Range。

**2. View (视图)**

**View** 是一种特殊的 Range，它具有以下关键特性：

* **轻量级 (Lightweight):** View 本身不拥有底层数据。它只是底层数据的一个“视图”或“引用”。这意味着复制、移动和销毁一个 View 的操作通常是常数时间复杂度 O(1)，与 View 所表示的元素数量无关。
* **非拥有 (Non-owning):** View 不管理底层数据的生命周期。View 的有效性依赖于它所引用的底层 Range 的生命周期。如果底层 Range 被销毁，那么引用它的 View 将会失效。
* **惰性求值 (Lazy Evaluation):** View 的操作是惰性执行的。当你创建一个 View 或者将多个 View 组合在一起时，实际的数据处理（如过滤、转换）并不会立即发生。这些操作只会在你实际迭代 View 并访问其元素时按需执行。

View 的主要目的是提供一种廉价的方式来转换、过滤或以其他方式操作 Range，而无需创建中间的、拥有数据的容器。这对于构建数据处理管线非常有用，可以避免不必要的内存分配和数据复制。

View 也满足 `std::ranges::view` concept，这是一个比 `std::ranges::range` 更严格的 concept，额外要求了 O(1) 的移动操作以及（如果可复制）O(1) 的复制操作。

**3. Range Adaptor (范围适配器)**

**Range Adaptor** 是一种函数对象或函数，它接收一个或多个 Range 作为输入，并返回一个新的 View。它们是创建和组合 View 的主要方式。

Range Adaptors 可以通过函数调用的方式使用，更常见和方便的是通过管道操作符 `|` 进行链式调用，形成一个数据处理管线。这种管道语法使得连续应用多个操作变得非常直观，读起来就像数据流经一系列转换步骤。

标准库提供了许多预定义的 Range Adaptors，例如：

* `std::views::filter(predicate)`: 创建一个 View，只包含满足给定谓词的元素。
* `std::views::transform(function)`: 创建一个 View，其元素是原始 Range 元素经过给定函数转换后的结果。
* `std::views::take(n)`: 创建一个 View，包含原始 Range 的前 n 个元素。
* `std::views::drop(n)`: 创建一个 View，跳过原始 Range 的前 n 个元素，包含剩余元素。
* `std::views::reverse`: 创建一个 View，以反向顺序访问原始 Range 的元素。
* `std::views:: دلایل`: 创建一个生成等差序列的 View。

**总结它们之间的关系：**

* **Range** 是最基础的概念，表示一个可迭代的序列。
* **View** 是一种特殊的 Range，它是轻量级、非拥有且惰性求值的，适合用于表示对底层 Range 的转换或过滤结果。
* **Range Adaptor** 是创建 View 的工具，它们接收 Range (通常也接受 View，因为 View 也是 Range) 作为输入，并输出 View。Range Adaptors 通常通过管道操作符 `|` 进行链式调用，构建复杂的数据处理管线。

**示例：**

```cpp
#include <iostream>
#include <vector>
#include <ranges>
#include <numeric> // for std::iota

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 使用 Range Adaptors 构建一个管道
    // 过滤出偶数，然后将每个偶数平方，最后取出前3个
    auto processed_view = numbers
                        | std::views::filter([](int n){ return n % 2 == 0; }) // 过滤出偶数
                        | std::views::transform([](int n){ return n * n; }) // 将偶数平方
                        | std::views::take(3); // 取出前3个结果

    // 迭代 View 并打印结果（惰性求值在这里发生）
    std::cout << "Processed numbers: ";
    for (int n : processed_view) {
        std::cout << n << " ";
    }
    std::cout << std::endl; // 输出: Processed numbers: 4 16 36

    // 另一个例子：使用 iota 生成一个序列，然后过滤和转换
    auto generated_view = std::views::iota(1) // 从1开始的无限序列
                        | std::views::filter([](int n){ return n > 5; }) // 过滤出大于5的数
                        | std::views::take(5); // 取出前5个结果

    std::cout << "Generated numbers: ";
    for (int n : generated_view) {
        std::cout << n << " ";
    }
    std::cout << std::endl; // 输出: Generated numbers: 6 7 8 9 10

    return 0;
}
```

在这个示例中，`numbers` 和 `std::views::iota(1)` 都是 Range。`std::views::filter`, `std::views::transform`, `std::views::take` 都是 Range Adaptors，它们组合起来创建了 `processed_view` 和 `generated_view` 这两个 View。迭代 View 时，实际的过滤和转换操作才被执行。这种方式使得数据处理流程更加清晰和高效。