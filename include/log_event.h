#ifndef LOG_EVENT_H_
#define LOG_EVENT_H_

#include <memory>
#include <sstream>
#include <cstdarg>

#include "log.h"
#include "logger.h"
#include "log_level.h"

namespace sylar
{

// 日志事件
class LogEvent
{
public:
    LogEvent(LoggerPtr logger, LogLevel::Level level
            ,const char* file, int32_t line, uint32_t elapse
            ,uint32_t threadId, uint32_t fiberId, uint64_t time
            ,const std::string& threadName);

    // get方法
    const char* getFile() const;
    int32_t getLine() const;
    uint32_t getElapse() const;
    uint32_t getThreadId() const;
    uint32_t getFiberId() const;
    uint64_t getTime() const;
    const std::string& getThreadName() const;
    std::string getContent() const;
    LoggerPtr getLogger() const;
    LogLevel::Level getLevel() const;
    std::stringstream& getSS();

    // 格式化写入日志内容
    void format(const char* fmt, ...);          // 可变参数函数
    void format(const char* fmt, va_list al);   // 实际的执行函数
private:
    const char* file_ = nullptr;    // 文件名
    int32_t line_ = 0;              // 行号
    uint32_t elapse_ = 0;           // 程序启动到现在的毫秒
    uint32_t threadId_ = 0;         // 线程id
    uint32_t fiberId_ = 0;          // 协程id
    uint64_t time_ = 0;             // 时间戳
    std::string threadName_;        // 线程名称
    std::stringstream ss_;          // 日志内容流
    LoggerPtr logger_;// 日志器
    LogLevel::Level level_;         // 日志等级
};

}

#endif // LOG_EVENT_H_