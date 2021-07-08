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

}