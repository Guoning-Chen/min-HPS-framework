#include "log_appender.h"

namespace sylar
{

inline void LogAppender::setFormatter(LogFormatterPtr formatter)
{
    formatter_ = formatter;
}

inline LogFormatterPtr LogAppender::getformatter() const
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