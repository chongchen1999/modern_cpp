#include <iostream>
#include <set>
#include <string>

int main() {
    // 1. 创建set
    std::set<int> numbers;
    std::set<std::string> words = {"apple", "banana", "orange"};

    // 2. 插入元素
    numbers.insert(10);
    numbers.insert(30);
    numbers.insert(20);
    numbers.insert(40);
    numbers.insert(30); // 重复元素不会被插入

    words.insert("grape");
    words.insert("pear");

    // 3. 遍历set
    std::cout << "Numbers: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "Fruits: ";
    for (const auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << std::endl;

    // 4. 查找元素
    auto it = words.find("banana");
    if (it != words.end()) {
        std::cout << "Found banana in the set" << std::endl;
    }

    // 5. 删除元素
    words.erase("orange");
    numbers.erase(30);

    // 6. 检查元素是否存在
    if (numbers.count(20) > 0) {
        std::cout << "20 exists in the numbers set" << std::endl;
    }

    // 7. 获取set大小
    std::cout << "Numbers set size: " << numbers.size() << std::endl;
    std::cout << "Words set size: " << words.size() << std::endl;

    // 8. 清空set
    numbers.clear();
    std::cout << "After clear, numbers set size: " << numbers.size()
              << std::endl;

    return 0;
}