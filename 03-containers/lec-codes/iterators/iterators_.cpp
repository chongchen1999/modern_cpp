#include <forward_list>
#include <iostream>
#include <iterator>
#include <list>
#include <type_traits>
#include <unordered_set>
#include <vector>

// 辅助函数：打印迭代器类型信息（通过iterator_traits）
template <typename Iterator>
void print_iterator_type(const Iterator& it) {
    using Traits = std::iterator_traits<Iterator>;

    std::cout << "Category: ";
    if constexpr (std::is_same_v<typename Traits::iterator_category,
                                 std::input_iterator_tag>) {
        std::cout << "Input Iterator";
    } else if constexpr (std::is_same_v<typename Traits::iterator_category,
                                        std::output_iterator_tag>) {
        std::cout << "Output Iterator";
    } else if constexpr (std::is_same_v<typename Traits::iterator_category,
                                        std::forward_iterator_tag>) {
        std::cout << "Forward Iterator";
    } else if constexpr (std::is_same_v<typename Traits::iterator_category,
                                        std::bidirectional_iterator_tag>) {
        std::cout << "Bidirectional Iterator";
    } else if constexpr (std::is_same_v<typename Traits::iterator_category,
                                        std::random_access_iterator_tag>) {
        std::cout << "Random Access Iterator";
    }

    std::cout << "\nValue type: " << typeid(typename Traits::value_type).name()
              << "\nDifference type: "
              << typeid(typename Traits::difference_type).name()
              << "\nPointer type: " << typeid(typename Traits::pointer).name()
              << "\nReference type: "
              << typeid(typename Traits::reference).name() << "\n\n";
}

int main() {
    // 1. 输入迭代器示例（从cin读取）
    std::cout << "=== Input Iterator (istream_iterator) ===\n";
    std::istream_iterator<int> input_it(std::cin);
    std::cout << "First input value: " << *input_it << "\n";
    print_iterator_type(input_it);

    // 2. 输出迭代器示例（向cout写入）
    std::cout << "=== Output Iterator (ostream_iterator) ===\n";
    std::ostream_iterator<int> output_it(std::cout, " ");
    *output_it = 42; // 输出42到控制台
    print_iterator_type(output_it);

    // 3. 前向迭代器示例（forward_list）
    std::cout << "=== Forward Iterator (forward_list) ===\n";
    std::forward_list<int> flist = {1, 2, 3};
    auto flist_it = flist.begin();
    std::cout << "First element: " << *flist_it << "\n";
    ++flist_it; // 只能向前移动
    print_iterator_type(flist_it);

    // 4. 双向迭代器示例（list）
    std::cout << "=== Bidirectional Iterator (list) ===\n";
    std::list<int> list = {1, 2, 3};
    auto list_it = list.end();
    --list_it; // 可以反向移动
    std::cout << "Last element: " << *list_it << "\n";
    print_iterator_type(list_it);

    // 5. 随机访问迭代器示例（vector）
    std::cout << "=== Random Access Iterator (vector) ===\n";
    std::vector<int> vec = {1, 2, 3};
    auto vec_it = vec.begin();
    vec_it += 2; // 直接跳转到第3个元素
    std::cout << "Third element: " << *vec_it << "\n";
    print_iterator_type(vec_it);

    // 6. 连续迭代器示例（C++17的vector/array）
    std::cout << "=== Contiguous Iterator (vector) ===\n";
    // C++20起vector迭代器正式标记为contiguous
    auto contig_it = vec.begin();
    // 通过指针算术验证连续性
    int* ptr = &*contig_it;
    std::cout << "Memory address: " << ptr << "\n";
    print_iterator_type(contig_it);

    return 0;
}