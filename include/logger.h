#ifndef LOGGER_H_
#define LOGGER_H_

#include <memory>
#include <list>

#include "log_event.h"
#include "log_level.h"
#include "log_appender.h"

namespace sylar
{

class LogAppender;

// 日志器
class Logger : public std::enable_shared_from_this<Logger>
{
public:
    typedef std::shared_ptr<Logger> ptr;

    Logger(const std::string& name = "root");
    // 写入日志并指定日志级别
    void log(LogLevel::Level level, LogEvent::ptr event);

    // 写入各种类型的日志
    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(std::shared_ptr<LogAppender> appender);
    void deleteAppender(std::shared_ptr<LogAppender> appender);
    
    LogLevel::Level getLevel() const;
    void setLevel(LogLevel::Level val);

    const std::string& getName() const;
private:
    std::string name_;      // 日志名称
    LogLevel::Level level_; // 日志级别
    std::list<std::shared_ptr<LogAppender>> appenders_; // Appender集合
};

}

#endif // LOGGER_H_