// utilities.hh
#ifndef UTILITIES_HH
#define UTILITIES_HH
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdarg>
#include "config.hh"

// 辅助函数，用于将任意类型转换为字符串
template<typename T>
std::string to_string_helper(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

// 定义日志级别
enum LogLevel {
    DEBUG,  // 调试信息
    INFO,   // 一般信息
    ERROR   // 错误信息
};

// 根据g_debug_mode自动设置全局日志级别
inline LogLevel lv = g_debug_mode ? DEBUG : INFO;    

// C风格格式化函数 (printf风格，使用 %d, %f 等)
std::string f(const char* format, ...);

// Python风格格式化函数 (使用 {} 作为占位符)
template<typename... Args>
std::string fmt(const std::string& format, Args... args) {
    std::vector<std::string> arguments{to_string_helper(args)...};
    std::string result;
    std::size_t lastPos = 0;
    std::size_t pos = 0;

    std::vector<std::string>::size_type argIndex = 0;
    while ((pos = format.find("{}", lastPos)) != std::string::npos) {
        result.append(format, lastPos, pos - lastPos); // 添加前一个{}之前的文本
        if (argIndex < arguments.size()) {
            result += arguments[argIndex++]; // 添加参数
        }
        lastPos = pos + 2; // 更新位置，跳过{}
    }
    result += format.substr(lastPos); // 添加剩余文本
    return result;
}

// 打印日志函数
void myPrint(LogLevel level, const std::string& message);

// 初始化日志级别函数
void InitializeLogLevel();

// 全局日志级别变量在utilities.cc中定义


#endif // UTILITIES_HH