#include "log_level.h"

namespace sylar
{

const char* LogLevel::toString(LogLevel::Level level)
{
    switch (level)
    {
        #define ENUM2STRIG(name) \
            case LogLevel::name: \
                return #name; \
                break;
            ENUM2STRIG(DEBUG);
            ENUM2STRIG(INFO);
            ENUM2STRIG(WARN);
            ENUM2STRIG(ERROR);
            ENUM2STRIG(FATAL);
        #undef ENUM2STRIG
    default:
        return "UNKNOWN";
    }
    return "UNKNOWN";
}

}