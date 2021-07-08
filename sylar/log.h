#ifndef __SYLAR_LOG_H_
#define __SYLAR_LOG_H_

#include <string>
#include <stdint.h>
#include <memory>
#include <list>

namespace sylar
{

// 日志事件
class LogEvent
{
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent();

private:
    const char* file_ = nullptr;// 文件名
    int32_t line_ = 0;          // 行号
    uint32_t elapse_ = 0;       // 程序启动到现在的毫秒
    uint32_t threadId_ = 0;     // 线程id
    uint32_t fiberId = 0;       // 协程id
    uint64_t time_;             // 时间戳
    std::string content_;
};

// 日志级别
class LogLevel
{
public:
    enum Level
    {
        DEBUG = 1,
        INFO  = 2,
        WARN  = 3,
        ERROR = 4,
        FATAL = 5
    };
};

// 日志格式器
class LogFormatter
{
public:
    typedef std::shared_ptr<LogFormatter> ptr;

    std::string format(LogEvent::ptr event);
private:
};

// 日志输出地
class LogAppender
{
public:
    typedef std::shared_ptr<LogAppender> ptr;
    virtual ~LogAppender();

    virtual void log(LogLevel::Level level, LogEvent::ptr event) = 0; // 纯虚函数
protected:
    LogLevel::Level level_;
};


// 日志器
class Logger
{
public:
    typedef std::shared_ptr<Logger> ptr;
    Logger(const std::string& name = "root");
    void log(LogLevel::Level level, LogEvent::ptr event);

    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);
    void deleteAppender(LogAppender::ptr appender);
    LogLevel::Level getLevel() const;
    void setLevel(LogLevel::Level val);
private:
    std::string name_;                      // 日志名称
    LogLevel::Level level_;                 // 日志级别
    std::list<LogAppender::ptr> appenders_; // Appender集合
};

// 定义输出到控制台的Appender
class StdoutLogAppender : public LogAppender
{
public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;
    void log(LogLevel::Level level, LogEvent::ptr event) override;
private:
};

// 定义输出到文件的Appender
class FileLogAppender : public LogAppender
{
public:
    typedef std::shared_ptr<FileLogAppender> ptr;
    FileLogAppender(const std::string& filename);
    void log(LogLevel::Level level, LogEvent::ptr event) override;
private:
    std::string filename_;
    std::ofstream fileStream_;
};

}

#endif // __SYLAR_LOG_H_
