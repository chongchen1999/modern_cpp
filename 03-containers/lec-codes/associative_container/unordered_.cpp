#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

int main() {
    // 1. unordered_set 示例
    std::unordered_set<std::string> uset = {"apple", "banana", "cherry"};

    // 插入元素
    uset.insert("date");
    uset.insert("apple"); // 不会重复插入

    std::cout << "unordered_set elements: ";
    for (const auto& fruit : uset) {
        std::cout << fruit << " ";
    }
    std::cout << "\n\n";

    // 2. unordered_map 示例
    std::unordered_map<std::string, int> umap = {
        {"Alice", 25}, {"Bob", 30}, {"Charlie", 35}};

    // 插入元素
    umap["David"] = 40;
    umap.insert({"Eve", 45});

    std::cout << "unordered_map elements:\n";
    for (const auto& pair : umap) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }
    std::cout << "\n";

    // 3. 查找操作
    // 在unordered_set中查找
    auto it = uset.find("banana");
    if (it != uset.end()) {
        std::cout << "Found banana in the set\n";
    }

    // 在unordered_map中查找
    if (umap.count("Alice") > 0) {
        std::cout << "Alice's age is " << umap["Alice"] << "\n";
    }

    // 4. 桶接口和哈希策略
    std::cout << "\nunordered_map statistics:\n";
    std::cout << "Load factor: " << umap.load_factor() << "\n";
    std::cout << "Bucket count: " << umap.bucket_count() << "\n";
    std::cout << "Max load factor: " << umap.max_load_factor() << "\n";

    return 0;
}