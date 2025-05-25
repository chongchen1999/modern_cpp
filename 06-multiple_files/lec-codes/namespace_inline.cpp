#include <iostream>

// inline namespace示例
namespace Lib {
    namespace v1 { // 普通嵌套namespace
        void func() {
            std::cout << "v1 function" << std::endl;
        }
    } // namespace v1

    namespace v2 { // inline namespace
        void func() {
            std::cout << "v2 function" << std::endl;
        }
    } // namespace v2

    inline namespace v3 { // 另一个inline namespace
        void func() {
            std::cout << "v3 function" << std::endl;
        }
    } // namespace v3 
} // namespace Lib

int main() {
    // 访问普通嵌套namespace需要完整路径
    Lib::v1::func(); // 输出: v1 function

    // inline namespace中的成员可以直接通过父namespace访问
    Lib::func(); // 输出: v2 function

    // 也可以显式指定inline namespace
    Lib::v2::func(); // 输出: v2 function

    return 0;
}