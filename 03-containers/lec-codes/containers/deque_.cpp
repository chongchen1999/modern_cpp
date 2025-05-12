#include <algorithm> // 用于std::sort
#include <deque>
#include <iostream>

// 打印deque的元素
void printDeque(const std::deque<int>& dq, const std::string& msg = "") {
    if (!msg.empty()) {
        std::cout << msg << ": ";
    }
    for (const auto& elem : dq) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}

int main() {
    // 1. 初始化deque
    std::deque<int> dq = {10, 20, 30};
    printDeque(dq, "初始deque");

    // 2. 头部和尾部插入
    dq.push_front(5); // 头部插入5
    dq.push_back(40); // 尾部插入40
    printDeque(dq, "头部插入5，尾部插入40后");

    // 3. 随机访问
    std::cout << "第二个元素（下标1）: " << dq[1] << "\n";
    std::cout << "第三个元素（at(2)）: " << dq.at(2) << "\n";

    // 4. 删除元素
    dq.pop_front(); // 删除头部
    dq.pop_back();  // 删除尾部
    printDeque(dq, "删除头尾后");

    // 5. 中间插入和删除
    dq.insert(dq.begin() + 1, 99); // 在第2个位置插入99
    printDeque(dq, "在位置1插入99后");

    dq.erase(dq.begin() + 2); // 删除第3个元素
    printDeque(dq, "删除位置2的元素后");

    // 6. 排序（deque支持随机访问迭代器）
    std::sort(dq.begin(), dq.end());
    printDeque(dq, "排序后");

    // 7. 清空deque
    dq.clear();
    std::cout << "清空后是否为空? " << (dq.empty() ? "是" : "否") << "\n";

    // 8. 性能测试：对比头部插入与vector
    std::deque<int> perfDeque;
    std::cout << "\n性能测试：向deque头部插入10000个元素...\n";
    for (int i = 0; i < 10000; ++i) {
        perfDeque.push_front(i); // O(1)时间复杂度
    }
    std::cout << "deque头部插入完成。\n";

    return 0;
}