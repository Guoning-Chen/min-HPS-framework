#ifndef LOG_APPENDER_H_
#define LOG_APPENDER_H_

#include <memory>

#include "log.h"
#include "log_formatter.h"
#include "log_level.h"
#include "logger.h"

namespace sylar
{

// 日志输出地
class LogAppender
{
public:
    virtual ~LogAppender();

    virtual void log(LoggerPtr, LogLevel::Level level, LogEventPtr event) = 0;

    void setFormatter(LogFormatterPtr formatter);
    LogFormatterPtr getformatter() const;
    LogLevel::Level getLevel() const;
    void setLevel(LogLevel::Level level);
protected:
    LogLevel::Level level_;
    LogFormatterPtr formatter_;
};

}

#endif // LOG_APPENDER_H_