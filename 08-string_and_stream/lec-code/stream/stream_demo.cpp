#include <fstream>  // 文件流
#include <iomanip>  // 流操纵符
#include <iostream> // 标准输入输出流
#include <sstream>  // 字符串流
#include <string>
#include <vector>

using namespace std;

// ============================================================================
// 1. 基础输入输出流 (iostream)
// ============================================================================
void demonstrateBasicIO() {
    cout << "\n=== 1. 基础输入输出流演示 ===" << endl;

    // cout - 标准输出流
    cout << "这是标准输出" << endl;

    // cerr - 标准错误流（无缓冲）
    cerr << "这是错误输出流" << endl;

    // clog - 标准日志流（有缓冲）
    clog << "这是日志输出流" << endl;

    // cin - 标准输入流
    cout << "请输入你的姓名: ";
    string name;
    getline(cin, name); // 使用getline读取整行
    cout << "你好, " << name << "!" << endl;

    // 流状态检查
    cout << "cin状态 - good(): " << cin.good() << ", eof(): " << cin.eof()
         << ", fail(): " << cin.fail() << ", bad(): " << cin.bad() << endl;
}

// ============================================================================
// 2. 流操纵符 (Stream Manipulators)
// ============================================================================
void demonstrateManipulators() {
    cout << "\n=== 2. 流操纵符演示 ===" << endl;

    int num = 255;
    double pi = 3.14159265359;

    // 数字格式化
    cout << "十进制: " << dec << num << endl;
    cout << "十六进制: " << hex << num << endl;
    cout << "八进制: " << oct << num << endl;
    cout << "恢复十进制: " << dec << num << endl;

    // 浮点数精度控制
    cout << "默认精度: " << pi << endl;
    cout << "设置精度为3: " << setprecision(3) << pi << endl;
    cout << "固定小数点: " << fixed << setprecision(2) << pi << endl;
    cout << "科学计数法: " << scientific << setprecision(4) << pi << endl;

    // 字段宽度和对齐
    cout << "默认对齐: |" << setw(10) << "Hello"
         << "|" << endl;
    cout << "左对齐: |" << left << setw(10) << "Hello"
         << "|" << endl;
    cout << "右对齐: |" << right << setw(10) << "Hello"
         << "|" << endl;
    cout << "居中填充: |" << setfill('*') << setw(10) << "Hello"
         << "|" << endl;

    // 恢复默认设置
    cout << setfill(' ') << resetiosflags(ios::adjustfield | ios::floatfield);
}

// ============================================================================
// 3. 文件流 (fstream)
// ============================================================================
void demonstrateFileStreams() {
    cout << "\n=== 3. 文件流演示 ===" << endl;

    // 写入文件 (ofstream)
    {
        ofstream outFile("demo.txt");
        if (outFile.is_open()) {
            outFile << "这是第一行文本" << endl;
            outFile << "数字: " << 42 << endl;
            outFile << "浮点数: " << 3.14 << endl;
            outFile << "布尔值: " << boolalpha << true << endl;
            cout << "成功写入文件 demo.txt" << endl;
        } else {
            cerr << "无法打开文件进行写入" << endl;
        }
    } // ofstream自动关闭

    // 读取文件 (ifstream)
    {
        ifstream inFile("demo.txt");
        if (inFile.is_open()) {
            cout << "从文件读取内容:" << endl;
            string line;
            while (getline(inFile, line)) {
                cout << "  " << line << endl;
            }
        } else {
            cerr << "无法打开文件进行读取" << endl;
        }
    }

    // 追加模式写入
    {
        ofstream appendFile("demo.txt", ios::app);
        if (appendFile.is_open()) {
            appendFile << "这是追加的内容" << endl;
            cout << "成功追加内容到文件" << endl;
        }
    }

    // 二进制文件操作
    {
        // 写入二进制数据
        ofstream binOut("binary_demo.bin", ios::binary);
        if (binOut.is_open()) {
            int numbers[] = {1, 2, 3, 4, 5};
            binOut.write(reinterpret_cast<char*>(numbers), sizeof(numbers));
            cout << "写入二进制文件成功" << endl;
        }

        // 读取二进制数据
        ifstream binIn("binary_demo.bin", ios::binary);
        if (binIn.is_open()) {
            int readNumbers[5];
            binIn.read(reinterpret_cast<char*>(readNumbers),
                       sizeof(readNumbers));
            cout << "从二进制文件读取: ";
            for (int i = 0; i < 5; i++) {
                cout << readNumbers[i] << " ";
            }
            cout << endl;
        }
    }
}

// ============================================================================
// 4. 字符串流 (stringstream)
// ============================================================================
void demonstrateStringStreams() {
    cout << "\n=== 4. 字符串流演示 ===" << endl;

    // ostringstream - 输出字符串流
    {
        ostringstream oss;
        oss << "姓名: "
            << "张三"
            << ", 年龄: " << 25 << ", 分数: " << 95.5;
        string result = oss.str();
        cout << "构造的字符串: " << result << endl;
    }

    // istringstream - 输入字符串流
    {
        string data = "100 3.14 Hello World";
        istringstream iss(data);

        int intVal;
        double doubleVal;
        string word1, word2;

        iss >> intVal >> doubleVal >> word1 >> word2;

        cout << "解析结果:" << endl;
        cout << "  整数: " << intVal << endl;
        cout << "  浮点数: " << doubleVal << endl;
        cout << "  字符串1: " << word1 << endl;
        cout << "  字符串2: " << word2 << endl;
    }

    // stringstream - 双向字符串流
    {
        stringstream ss;

        // 写入数据
        ss << "温度: " << 25.5 << "°C";
        cout << "stringstream内容: " << ss.str() << endl;

        // 清空并重新写入
        ss.str(""); // 清空内容
        ss.clear(); // 清空状态标志

        vector<int> numbers = {1, 2, 3, 4, 5};
        for (size_t i = 0; i < numbers.size(); i++) {
            if (i > 0)
                ss << ",";
            ss << numbers[i];
        }
        cout << "数组转字符串: " << ss.str() << endl;

        // 从stringstream读取
        ss.str("10 20 30 40 50");
        ss.clear();

        int num;
        vector<int> parsed;
        while (ss >> num) {
            parsed.push_back(num);
        }
        cout << "解析的数字: ";
        for (int n : parsed) {
            cout << n << " ";
        }
        cout << endl;
    }
}

// ============================================================================
// 5. 流的状态管理
// ============================================================================
void demonstrateStreamStates() {
    cout << "\n=== 5. 流状态管理演示 ===" << endl;

    stringstream ss("123 abc");

    // 正常读取
    int num;
    ss >> num;
    cout << "读取数字: " << num << endl;
    cout << "流状态 - good: " << ss.good() << ", fail: " << ss.fail() << endl;

    // 尝试读取非数字
    int invalid;
    ss >> invalid;
    cout << "尝试读取非数字后的状态:" << endl;
    cout << "  good: " << ss.good() << endl;
    cout << "  fail: " << ss.fail() << endl;
    cout << "  bad: " << ss.bad() << endl;
    cout << "  eof: " << ss.eof() << endl;

    // 清除错误状态
    ss.clear();
    cout << "清除错误状态后 - good: " << ss.good() << endl;

    // 跳过错误的输入
    string skipStr;
    ss >> skipStr;
    cout << "跳过的字符串: " << skipStr << endl;
}

// ============================================================================
// 6. 高级流操作
// ============================================================================
void demonstrateAdvancedStreamOps() {
    cout << "\n=== 6. 高级流操作演示 ===" << endl;

    // 流缓冲区操作
    cout << "流缓冲区操作:" << endl;
    cout << "输出不换行1 ";
    cout.flush(); // 强制刷新缓冲区
    cout << "输出不换行2" << endl;

    // 流的链式操作
    ostringstream chain;
    chain << "链式操作: " << setw(10) << left << "姓名" << setw(5) << right
          << "年龄" << setw(8) << "分数" << endl;
    chain << setfill('-') << setw(23) << "" << setfill(' ') << endl;
    chain << setw(10) << left << "张三" << setw(5) << right << 20 << setw(8)
          << 85.5 << endl;

    cout << chain.str();

    // 文件位置操作
    {
        fstream file("position_demo.txt", ios::out | ios::in | ios::trunc);
        if (file.is_open()) {
            // 写入数据
            file << "0123456789ABCDEF";

            // 移动到文件开头
            file.seekg(0, ios::beg);
            char ch;
            file >> ch;
            cout << "文件开头字符: " << ch << endl;

            // 移动到文件中间
            file.seekg(5, ios::beg);
            file >> ch;
            cout << "位置5的字符: " << ch << endl;

            // 获取当前位置
            streampos pos = file.tellg();
            cout << "当前位置: " << pos << endl;

            // 移动到文件末尾
            file.seekg(0, ios::end);
            cout << "文件大小: " << file.tellg() << " 字节" << endl;
        }
    }
}

// ============================================================================
// 7. 自定义流操纵符
// ============================================================================
// 自定义操纵符：输出分隔线
ostream& separator(ostream& os) {
    return os << "\n" << string(50, '=') << "\n";
}

// 带参数的自定义操纵符
class repeat {
    char ch;
    int count;

public:
    repeat(char c, int n) : ch(c), count(n) {}
    friend ostream& operator<<(ostream& os, const repeat& r) {
        return os << string(r.count, r.ch);
    }
};

void demonstrateCustomManipulators() {
    cout << "\n=== 7. 自定义流操纵符演示 ===" << endl;

    cout << "使用自定义分隔线:" << separator;
    cout << "分隔线上方" << separator;
    cout << "分隔线下方" << endl;

    cout << "\n使用带参数的自定义操纵符:" << endl;
    cout << "星号: " << repeat('*', 20) << endl;
    cout << "等号: " << repeat('=', 15) << endl;
    cout << "减号: " << repeat('-', 25) << endl;
}

// ============================================================================
// 8. 实际应用示例
// ============================================================================
struct Student {
    string name;
    int age;
    double grade;

    // 重载输出操作符
    friend ostream& operator<<(ostream& os, const Student& s) {
        return os << setw(10) << left << s.name << setw(5) << right << s.age
                  << setw(8) << fixed << setprecision(1) << s.grade;
    }

    // 重载输入操作符
    friend istream& operator>>(istream& is, Student& s) {
        return is >> s.name >> s.age >> s.grade;
    }
};

void demonstrateRealWorldExample() {
    cout << "\n=== 8. 实际应用示例 ===" << endl;

    vector<Student> students = {
        {"张三", 20, 85.5}, {"李四", 21, 92.0}, {"王五", 19, 78.5}};

    // 格式化输出到控制台
    cout << "\n学生信息表:" << endl;
    cout << setw(10) << left << "姓名" << setw(5) << right << "年龄" << setw(8)
         << "成绩" << endl;
    cout << string(23, '-') << endl;

    for (const auto& student : students) {
        cout << student << endl;
    }

    // 保存到文件
    {
        ofstream file("students.txt");
        if (file.is_open()) {
            for (const auto& student : students) {
                file << student.name << " " << student.age << " "
                     << student.grade << endl;
            }
            cout << "\n学生信息已保存到 students.txt" << endl;
        }
    }

    // 从文件读取
    {
        ifstream file("students.txt");
        if (file.is_open()) {
            cout << "\n从文件读取的学生信息:" << endl;
            Student s;
            while (file >> s) {
                cout << s << endl;
            }
        }
    }

    // 使用stringstream进行数据转换
    ostringstream report;
    report << "=== 学生成绩报告 ===" << endl;
    double totalGrade = 0;
    for (const auto& student : students) {
        report << student.name << ": " << student.grade << "分" << endl;
        totalGrade += student.grade;
    }
    report << "平均分: " << fixed << setprecision(1)
           << totalGrade / students.size() << "分" << endl;

    cout << "\n" << report.str();
}

// ============================================================================
// 主函数
// ============================================================================
int main() {
    cout << "C++ Stream 完整演示程序" << endl;
    cout << string(60, '=') << endl;

    try {
        demonstrateBasicIO();
        demonstrateManipulators();
        demonstrateFileStreams();
        demonstrateStringStreams();
        demonstrateStreamStates();
        demonstrateAdvancedStreamOps();
        demonstrateCustomManipulators();
        demonstrateRealWorldExample();

    } catch (const exception& e) {
        cerr << "程序执行出错: " << e.what() << endl;
        return 1;
    }

    cout << "\n" << string(60, '=') << endl;
    cout << "演示程序执行完毕！" << endl;

    return 0;
}

/*
编译和运行说明:
1. 编译: g++ -o stream_demo stream_demo.cpp
2. 运行: ./stream_demo

程序会创建以下文件:
- demo.txt: 文本文件演示
- binary_demo.bin: 二进制文件演示
- position_demo.txt: 文件位置操作演示
- students.txt: 学生信息文件

C++ Stream 核心概念总结:

1. Stream层次结构:
   - ios: 所有流的基类
   - istream: 输入流基类 (cin)
   - ostream: 输出流基类 (cout, cerr, clog)
   - iostream: 双向流基类
   - fstream: 文件流
   - stringstream: 字符串流

2. 主要Stream类型:
   - iostream: 标准输入输出流
   - fstream: 文件流 (ifstream, ofstream, fstream)
   - stringstream: 字符串流 (istringstream, ostringstream, stringstream)

3. Stream特性:
   - 缓冲: 提高I/O效率
   - 类型安全: 编译时类型检查
   - 可扩展: 可以重载操作符
   - 格式化: 丰富的格式控制
   - 状态管理: good(), fail(), bad(), eof()

4. 常用操作:
   - 输入输出: << >> 操作符
   - 格式控制: setw(), setprecision(), fixed等
   - 文件操作: 打开、读写、关闭
   - 字符串转换: 与其他数据类型互转
   - 位置控制: seekg(), seekp(), tellg(), tellp()

这个程序涵盖了C++ Stream的所有重要概念和实际应用场景。
*/