#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

using namespace std;

void vectorIteratorInvalidation() {
    cout << "=== Vector Iterator Invalidation ===" << endl;
    vector<int> vec = {1, 2, 3, 4, 5};

    auto it = vec.begin() + 2; // 指向3
    cout << "Before insertion: " << *it << endl;

    // 插入元素可能导致重新分配
    vec.insert(vec.begin(), 0); // 所有迭代器失效

    // 危险！解引用失效的迭代器是未定义行为
    // cout << "After insertion: " << *it << endl; // 不要这样做！

    // 正确做法：重新获取迭代器
    it = vec.begin() + 3;
    cout << "After insertion (reacquired): " << *it << endl;

    // 删除元素使被删及之后的迭代器失效
    auto it2 = vec.begin() + 1;
    cout << "Before erase: " << *it2 << endl;
    vec.erase(vec.begin()); // 删除第一个元素

    cout << "After erase: " << *it2
         << endl; // it2仍然有效，指向原第二个元素(现在是第一个)
}

void listIteratorInvalidation() {
    cout << "\n=== List Iterator Invalidation ===" << endl;
    list<int> lst = {1, 2, 3, 4, 5};

    auto it = next(lst.begin(), 2); // 指向3
    cout << "Before erase: " << *it << endl;

    // 删除元素只使被删元素的迭代器失效
    auto it2 = next(lst.begin(), 1); // 指向2
    lst.erase(it2);                  // 删除2

    cout << "After erase: " << *it << endl; // it仍然有效，指向3

    // 插入不会使任何迭代器失效
    lst.insert(lst.begin(), 0);
    cout << "After insert: " << *it << endl; // it仍然有效，指向3
}

void unorderedMapIteratorInvalidation() {
    cout << "\n=== Unordered Map Iterator Invalidation ===" << endl;
    unordered_map<int, string> umap = {{1, "one"}, {2, "two"}, {3, "three"}};

    auto it = umap.find(2);
    cout << "Before erase: " << it->second << endl;

    // 删除元素只使被删元素的迭代器失效
    umap.erase(1); // 删除key=1

    cout << "After erase: " << it->second << endl; // it仍然有效

    // 插入可能导致rehash，但不使迭代器失效(标准保证)
    umap.insert({4, "four"});
    cout << "After insert: " << it->second << endl; // it仍然有效

    // 但删除当前迭代器会使它失效
    it = umap.find(2);
    umap.erase(it); // 使用迭代器删除

    // 现在it已失效，不能再使用
    // cout << "After erase by iterator: " << it->second << endl; // 危险！
}

int main() {
    vectorIteratorInvalidation();
    listIteratorInvalidation();
    unorderedMapIteratorInvalidation();

    return 0;
}