#include "log_level.h"

namespace sylar
{

const char* LogLevel::toString(LogLevel::Level level)
{
    switch (level)
    {
        #define XX(name) \
            case LogLevel::name: \
                return #name; \
                break;
            XX(DEBUG);
            XX(INFO);
            XX(WARN);
            XX(ERROR);
            XX(FATAL);
        #undef XX
    default:
        return "UNKNOWN";
    }
    return "UNKNOWN";
}

}