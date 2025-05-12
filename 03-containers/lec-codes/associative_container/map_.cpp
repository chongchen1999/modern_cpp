#include <iostream>
#include <map>
#include <string>

int main() {
    // 1. 创建一个map，键是string类型，值是int类型
    std::map<std::string, int> ageMap;

    // 2. 插入元素
    ageMap["Alice"] = 25;
    ageMap["Bob"] = 30;
    ageMap["Charlie"] = 35;

    // 另一种插入方式
    ageMap.insert(std::pair<std::string, int>("David", 40));
    ageMap.insert({"Eve", 28});

    // 3. 访问元素
    std::cout << "Alice's age: " << ageMap["Alice"] << std::endl;

    // 4. 检查元素是否存在
    if (ageMap.find("Frank") == ageMap.end()) {
        std::cout << "Frank not found in the map." << std::endl;
    }

    // 5. 遍历map
    std::cout << "\nAll entries in the map:" << std::endl;
    for (const auto& pair : ageMap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // 6. 使用迭代器遍历
    std::cout << "\nUsing iterator:" << std::endl;
    for (auto it = ageMap.begin(); it != ageMap.end(); ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }

    // 7. 获取map大小
    std::cout << "\nMap size: " << ageMap.size() << std::endl;

    // 8. 删除元素
    ageMap.erase("Bob");
    std::cout << "\nAfter erasing Bob, map size: " << ageMap.size()
              << std::endl;

    // 9. 清空map
    ageMap.clear();
    std::cout << "After clear, map size: " << ageMap.size() << std::endl;

    return 0;
}