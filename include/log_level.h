#ifndef LOG_LEVEL_H_
#define LOG_LEVEL_H_

#include <memory>

#include "log.h"

namespace sylar
{

// 日志级别
class LogLevel
{
public:
    enum Level
    {
        UNKNOWN = 0,
        DEBUG = 1,
        INFO  = 2,
        WARN  = 3,
        ERROR = 4,
        FATAL = 5
    };

    static const char* toString(LogLevel::Level level);
};

}

#endif // LOG_LEVEL_H_