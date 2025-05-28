#include <iostream>
#include <string>

int main() {
    // Character literals
    std::cout << "=== Character Literals ===" << std::endl;
    char c1 = 'a';    // simple character
    char c2 = '\n';   // escaped character (newline)
    char c3 = '\\';   // escaped backslash
    char c4 = '\123'; // octal representation (S)
    char c5 = '\x12'; // hexadecimal representation (device control 2)
    // C++23 new formats (commented out as they require C++23)
    // char c6 = '\o{123}';         // new octal format
    // char c7 = '\x{12}';          // new hexadecimal format

    std::cout << "c1: " << c1 << std::endl;
    std::cout << "c2: " << c2 << " (newline)" << std::endl;
    std::cout << "c3: " << c3 << std::endl;
    std::cout << "c4: " << c4 << std::endl;
    std::cout << "c5: " << static_cast<int>(c5) << " (non-printable)"
              << std::endl;

    // C-style strings
    std::cout << "\n=== C-style Strings ===" << std::endl;
    const char* str1 =
        "abc\x12\n";         // contains a, b, c, \x12, \n, and null terminator
    auto str2 = "abc\x12\n"; // decays to const char*
    // char* str4 = "abc";          // error: cannot convert from const char* to
    // char*
    char* str3 = const_cast<char*>("abc"); // requires const_cast

    std::cout << "str1: " << str1 << " (contains non-printable characters)"
              << std::endl;
    std::cout << "str2: " << str2 << std::endl;
    std::cout << "str3: " << str3 << std::endl;

    // String concatenation
    std::cout << "\n=== String Concatenation ===" << std::endl;
    const char* concat = "123"
                         "456"; // same as "123456"
    const char* multiline = "This is a very long string that "
                            "spans multiple lines in the source "
                            "code but is a single string.";

    std::cout << "concat: " << concat << std::endl;
    std::cout << "multiline: " << multiline << std::endl;

    // Raw strings
    std::cout << "\n=== Raw Strings ===" << std::endl;
    const char* escaped = "\\\\\\n\\\""; // represents \\\n\"
    const char* raw = R"(\\\n\")";       // represents exactly \\\n\"
    const char* path = R"(C:\Program Files\MyApp\data.txt)"; // Windows path
    const char* newline_raw = R"(This is a
new line)"; // contains actual newline

    std::cout << "escaped: " << escaped << std::endl;
    std::cout << "raw: " << raw << std::endl;
    std::cout << "path: " << path << std::endl;
    std::cout << "newline_raw: " << newline_raw << std::endl;

    // Raw strings with custom delimiters
    std::cout << "\n=== Raw Strings with Custom Delimiters ===" << std::endl;
    const char* special_raw = R"+*(I want a )" in my string!)+*";

    std::cout << "special_raw: " << special_raw << std::endl;

    return 0;
}