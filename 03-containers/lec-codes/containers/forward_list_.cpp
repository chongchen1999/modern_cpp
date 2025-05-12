#include <algorithm> // for std::find
#include <forward_list>
#include <iostream>

using namespace std;

// 打印forward_list的函数
template <typename T>
void printList(const forward_list<T>& flist) {
    for (const auto& elem : flist) {
        cout << elem << " ";
    }
    cout << endl;
}

int main() {
    // 1. 创建和初始化forward_list
    forward_list<int> flist1 = {1, 2, 3, 4, 5};
    forward_list<string> flist2 = {"Apple", "Banana", "Cherry"};

    cout << "初始flist1: ";
    printList(flist1);
    cout << "初始flist2: ";
    printList(flist2);

    // 2. 访问元素
    cout << "flist1的第一个元素: " << flist1.front() << endl;

    // 3. 修改元素
    flist1.front() = 10;
    cout << "修改后flist1: ";
    printList(flist1);

    // 4. 添加元素
    flist1.push_front(0); // 在头部添加
    cout << "添加0后flist1: ";
    printList(flist1);

    // 5. 插入元素（在特定位置后插入）
    auto it = find(flist1.begin(), flist1.end(), 3);
    if (it != flist1.end()) {
        flist1.insert_after(it, 99); // 在3后面插入99
    }
    cout << "插入99后flist1: ";
    printList(flist1);

    // 6. 删除元素
    flist1.pop_front(); // 删除第一个元素
    cout << "删除第一个元素后flist1: ";
    printList(flist1);

    it = find(flist1.begin(), flist1.end(), 99);
    if (it != flist1.end()) {
        flist1.erase_after(it); // 删除99后面的元素
    }
    cout << "删除99后面的元素后flist1: ";
    printList(flist1);

    // 7. 合并两个forward_list
    forward_list<int> flist3 = {100, 200, 300};
    flist1.merge(flist3);
    cout << "合并后的flist1: ";
    printList(flist1);
    cout << "合并后的flist3是否为空: " << (flist3.empty() ? "是" : "否")
         << endl;

    // 8. 排序
    flist1.sort();
    cout << "排序后的flist1: ";
    printList(flist1);

    // 9. 反转
    flist1.reverse();
    cout << "反转后的flist1: ";
    printList(flist1);

    // 10. 删除特定值
    flist1.remove(10);
    cout << "删除所有10后的flist1: ";
    printList(flist1);

    // 11. 删除满足条件的元素
    flist1.remove_if([](int n) { return n > 100; });
    cout << "删除大于100的元素后的flist1: ";
    printList(flist1);

    // 12. 清空forward_list
    flist1.clear();
    cout << "清空后flist1是否为空: " << (flist1.empty() ? "是" : "否") << endl;

    return 0;
}