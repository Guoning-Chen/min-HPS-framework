#include "log_appender.h"

namespace sylar
{

inline void LogAppender::setFormatter(LogFormatter::ptr formatter)
{
    formatter_ = formatter;
}

inline LogFormatter::ptr LogAppender::getformatter() const
{
    return formatter_;
}

inline LogLevel::Level LogAppender::getLevel() const
{
    return level_;
}

inline void LogAppender::setLevel(LogLevel::Level level)
{
    level_ = level;
}

}