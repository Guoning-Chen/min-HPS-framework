#include <iostream>

#include "log_stdout_appender.h"

namespace sylar
{

void StdoutLogAppender::log(LoggerPtr logger, LogLevel::Level level, 
    LogEventPtr event)
{
    if (level >= level_)
        std::cout << formatter_->format(logger, level, event);
}

}