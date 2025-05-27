#include "calculator.h"
#include <gtest/gtest.h>

// 测试加法
TEST(CalculatorTest, AddPositiveNumbers) {
    Calculator calc;
    EXPECT_EQ(5, calc.Add(2, 3));
}

TEST(CalculatorTest, AddNegativeNumbers) {
    Calculator calc;
    EXPECT_EQ(-5, calc.Add(-2, -3));
}

// 测试减法
TEST(CalculatorTest, SubtractNumbers) {
    Calculator calc;
    EXPECT_EQ(1, calc.Subtract(4, 3));
    EXPECT_EQ(-1, calc.Subtract(3, 4));
}

// 测试除法
TEST(CalculatorTest, DivideNumbers) {
    Calculator calc;
    EXPECT_DOUBLE_EQ(2.5, calc.Divide(5, 2));
}

TEST(CalculatorTest, DivideByZero) {
    Calculator calc;
    EXPECT_THROW(calc.Divide(5, 0), std::invalid_argument);
}

// 参数化测试示例（测试加法交换律）
class AddTest : public ::testing::TestWithParam<std::tuple<int, int>> {};

TEST_P(AddTest, AdditionIsCommutative) {
    Calculator calc;
    int a = std::get<0>(GetParam());
    int b = std::get<1>(GetParam());

    EXPECT_EQ(calc.Add(a, b), calc.Add(b, a));
}

INSTANTIATE_TEST_SUITE_P(CommutativeTest, AddTest,
                         ::testing::Values(std::make_tuple(1, 2),
                                           std::make_tuple(-3, 5),
                                           std::make_tuple(0, 0),
                                           std::make_tuple(100, -100)));