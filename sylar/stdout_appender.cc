#include <iostream>

#include "stdout_appender.h"

namespace sylar
{

void StdoutLogAppender::log(LogLevel::Level level, LogEvent::ptr event)
{
    if (level >= level_)
        std::cout << formatter_->format(event);
}

}