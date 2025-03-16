// utilities.cc
#include "utilities.hh"
#include "config.hh"
#include <iostream>
#include <sstream>


// 格式化字符串函数
std::string f(const char* format, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    return std::string(buffer);
}

// 打印日志函数
void myPrint(LogLevel level, const std::string& message) {
    if (level >= lv) {  // 只显示级别高于或等于全局设置的日志
        std::string prefix;
        switch(level) {
            case DEBUG: prefix = "[DEBUG] "; break;
            case INFO:  prefix = "[INFO] ";  break;
            case ERROR: prefix = "[ERROR] "; break;
        }
        std::cout << prefix << message << std::endl;
    }
}

