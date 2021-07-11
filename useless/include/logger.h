#ifndef LOGGER_H_
#define LOGGER_H_

#include <memory>
#include <list>

#include "log.h"
#include "log_event.h"
#include "log_level.h"
#include "log_appender.h"

namespace sylar
{

// 日志器
class Logger : public std::enable_shared_from_this<Logger>
{
public:
    Logger(const std::string& name = "root");
    // 写入日志并指定日志级别
    void log(LogLevel::Level level, LogEventPtr event);

    // 写入各种类型的日志
    void debug(LogEventPtr event);
    void info(LogEventPtr event);
    void warn(LogEventPtr event);
    void error(LogEventPtr event);
    void fatal(LogEventPtr event);

    void addAppender(LogAppenderPtr appender);
    void deleteAppender(LogAppenderPtr appender);
    
    LogLevel::Level getLevel() const;
    void setLevel(LogLevel::Level val);

    const std::string& getName() const;
private:
    std::string name_;      // 日志名称
    LogLevel::Level level_; // 日志级别
    std::list<LogAppenderPtr> appenders_; // Appender集合
};

}

#endif // LOGGER_H_