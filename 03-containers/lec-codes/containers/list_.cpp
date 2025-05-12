#include <algorithm> // 包含算法头文件用于排序
#include <iostream>
#include <list> // 包含 list 头文件

// 打印 list 内容的辅助函数
template <typename T>
void printList(const std::list<T>& lst, const std::string& message = "") {
    if (!message.empty()) {
        std::cout << message << ": ";
    }
    for (const auto& elem : lst) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main() {
    // 1. 创建和初始化 list
    std::list<int> myList = {5, 2, 9, 1, 7};
    printList(myList, "初始 list");

    // 2. 添加元素
    myList.push_back(8);  // 在末尾添加元素
    myList.push_front(3); // 在开头添加元素
    printList(myList, "添加元素后");

    // 3. 插入元素
    auto it = std::find(myList.begin(), myList.end(), 9);
    if (it != myList.end()) {
        myList.insert(it, 6); // 在9之前插入6
    }
    printList(myList, "插入6后");

    // 4. 删除元素
    myList.pop_front(); // 删除第一个元素
    myList.pop_back();  // 删除最后一个元素
    printList(myList, "删除首尾元素后");

    // 删除特定元素
    myList.remove(2); // 删除所有值为2的元素
    printList(myList, "删除所有2后");

    // 5. 访问元素
    std::cout << "第一个元素: " << myList.front() << std::endl;
    std::cout << "最后一个元素: " << myList.back() << std::endl;

    // 6. 大小和容量
    std::cout << "list大小: " << myList.size() << std::endl;
    std::cout << "list是否为空: " << (myList.empty() ? "是" : "否")
              << std::endl;

    // 7. 排序
    myList.sort(); // list有专门的sort成员函数
    printList(myList, "排序后");

    // 8. 合并两个已排序的list
    std::list<int> otherList = {4, 10};
    otherList.sort();
    myList.merge(otherList);
    printList(myList, "合并后");
    std::cout << "otherList现在的大小: " << otherList.size() << std::endl;

    // 9. 反转list
    myList.reverse();
    printList(myList, "反转后");

    // 10. 删除重复元素(必须先排序)
    myList.sort();
    myList.unique();
    printList(myList, "去重后");

    // 11. 清空list
    myList.clear();
    std::cout << "清空后list大小: " << myList.size() << std::endl;

    return 0;
}