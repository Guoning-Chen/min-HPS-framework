#include <iostream>

#include "stdout_appender.h"

namespace sylar
{

void StdoutLogAppender::log(std::shared_ptr<Logger>logger, 
    LogLevel::Level level, LogEvent::ptr event)
{
    if (level >= level_)
        std::cout << formatter_->format(logger, level, event);
}

}