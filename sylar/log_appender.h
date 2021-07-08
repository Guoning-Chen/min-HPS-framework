#ifndef LOG_APPENDER_H_
#define LOG_APPENDER_H_

#include <memory>
#include "log_formatter.h"
#include "log_level.h"

namespace sylar
{

// 日志输出地
class LogAppender
{
public:
    typedef std::shared_ptr<LogAppender> ptr;
    virtual ~LogAppender();

    virtual void log(std::shared_ptr<Logger>logger, LogLevel::Level level, 
        LogEvent::ptr event) = 0;

    void setFormatter(LogFormatter::ptr formatter);
    LogFormatter::ptr getformatter() const;
protected:
    LogLevel::Level level_;
    LogFormatter::ptr formatter_;
};

}

#endif // LOG_APPENDER_H_