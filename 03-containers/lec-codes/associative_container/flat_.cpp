#include <algorithm>
#include <flat_map>
#include <flat_set>
#include <iostream>
#include <string>
#include <vector>

int main() {
    // ========== flat_set 示例 ==========
    std::cout << "=== flat_set 示例 ===\n";

    // 创建并初始化一个 flat_set
    std::flat_set<int> fs = {5, 2, 8, 3, 1, 9, 4};

    // 自动保持有序
    std::cout << "flat_set 内容: ";
    for (int n : fs) {
        std::cout << n << " ";
    }
    std::cout << "\n";

    // 查找元素
    auto it = fs.find(3);
    if (it != fs.end()) {
        std::cout << "找到元素 3\n";
    }

    // 插入元素
    fs.insert(6);
    std::cout << "插入 6 后: ";
    for (int n : fs) {
        std::cout << n << " ";
    }
    std::cout << "\n";

    // 删除元素
    fs.erase(2);
    std::cout << "删除 2 后: ";
    for (int n : fs) {
        std::cout << n << " ";
    }
    std::cout << "\n\n";

    // ========== flat_map 示例 ==========
    std::cout << "=== flat_map 示例 ===\n";

    // 创建并初始化一个 flat_map
    std::flat_map<std::string, int> fm = {
        {"apple", 5}, {"banana", 3}, {"orange", 7}, {"pear", 2}};

    // 自动按键排序
    std::cout << "flat_map 内容:\n";
    for (const auto& [key, value] : fm) {
        std::cout << key << ": " << value << "\n";
    }

    // 查找元素
    auto it2 = fm.find("banana");
    if (it2 != fm.end()) {
        std::cout << "找到 banana, 数量: " << it2->second << "\n";
    }

    // 插入元素
    fm.insert({"grape", 4});
    std::cout << "\n插入 grape 后:\n";
    for (const auto& [key, value] : fm) {
        std::cout << key << ": " << value << "\n";
    }

    // 修改元素
    fm["orange"] = 8;
    std::cout << "\n修改 orange 数量后:\n";
    for (const auto& [key, value] : fm) {
        std::cout << key << ": " << value << "\n";
    }

    // 删除元素
    fm.erase("pear");
    std::cout << "\n删除 pear 后:\n";
    for (const auto& [key, value] : fm) {
        std::cout << key << ": " << value << "\n";
    }

    return 0;
}