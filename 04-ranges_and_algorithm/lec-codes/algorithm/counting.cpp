#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    // 创建一个测试用的vector
    std::vector<int> numbers = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};

    // 定义一些谓词函数
    auto isEven = [](int x) { return x % 2 == 0; };
    auto isOdd = [](int x) { return x % 2 != 0; };
    auto isGreaterThan5 = [](int x) { return x > 5; };

    // 演示std::all_of - 检查是否所有元素都满足谓词
    bool allEven = std::all_of(numbers.begin(), numbers.end(), isEven);
    bool allOdd = std::all_of(numbers.begin(), numbers.end(), isOdd);

    std::cout << "是否所有元素都是偶数: " << (allEven ? "是" : "否")
              << std::endl;
    std::cout << "是否所有元素都是奇数: " << (allOdd ? "是" : "否")
              << std::endl;

    // 演示std::any_of - 检查是否至少有一个元素满足谓词
    bool anyEven = std::any_of(numbers.begin(), numbers.end(), isEven);
    bool anyGreaterThan5 =
        std::any_of(numbers.begin(), numbers.end(), isGreaterThan5);

    std::cout << "是否存在偶数元素: " << (anyEven ? "是" : "否") << std::endl;
    std::cout << "是否存在大于5的元素: " << (anyGreaterThan5 ? "是" : "否")
              << std::endl;

    // 演示std::none_of - 检查是否没有元素满足谓词
    bool noneEven = std::none_of(numbers.begin(), numbers.end(), isEven);
    bool noneGreaterThan20 = std::none_of(numbers.begin(), numbers.end(),
                                          [](int x) { return x > 20; });

    std::cout << "是否没有偶数元素: " << (noneEven ? "是" : "否") << std::endl;
    std::cout << "是否没有大于20的元素: " << (noneGreaterThan20 ? "是" : "否")
              << std::endl;

    // 演示std::count - 计算特定值出现的次数
    int countOf5 = std::count(numbers.begin(), numbers.end(), 5);
    int countOf11 = std::count(numbers.begin(), numbers.end(), 11);

    std::cout << "数字5出现的次数: " << countOf5 << std::endl;
    std::cout << "数字11出现的次数: " << countOf11 << std::endl;

    // 演示std::count_if - 计算满足谓词的元素个数
    int countEven = std::count_if(numbers.begin(), numbers.end(), isEven);
    int countOdd = std::count_if(numbers.begin(), numbers.end(), isOdd);
    int countGreaterThan5 =
        std::count_if(numbers.begin(), numbers.end(), isGreaterThan5);

    std::cout << "偶数元素的个数: " << countEven << std::endl;
    std::cout << "奇数元素的个数: " << countOdd << std::endl;
    std::cout << "大于5的元素个数: " << countGreaterThan5 << std::endl;

    return 0;
}