#ifndef LOG_APPENDER_H_
#define LOG_APPENDER_H_

#include <memory>
#include "log_formatter.h"
#include "log_level.h"
#include "logger.h"

namespace sylar
{

class Logger;
class LogFormatter;

// 日志输出地
class LogAppender
{
public:
    typedef std::shared_ptr<LogAppender> ptr;

    virtual ~LogAppender();

    virtual void log(std::shared_ptr<Logger>logger, LogLevel::Level level, 
        LogEvent::ptr event) = 0;

    void setFormatter(std::shared_ptr<LogFormatter> formatter);
    std::shared_ptr<LogFormatter> getformatter() const;
    LogLevel::Level getLevel() const;
    void setLevel(LogLevel::Level level);
protected:
    LogLevel::Level level_;
    std::shared_ptr<LogFormatter> formatter_;
};

}

#endif // LOG_APPENDER_H_