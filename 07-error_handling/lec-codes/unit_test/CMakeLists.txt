cmake_minimum_required(VERSION 3.10)
project(CalculatorTest)

# 查找 GoogleTest
find_package(GTest REQUIRED)

# 添加可执行文件
add_executable(calculator_test
    calculator.cpp
    calculator_test.cpp
    main.cpp
)

# 链接 GoogleTest
target_link_libraries(calculator_test GTest::GTest GTest::Main)