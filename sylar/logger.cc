#include "logger.h"

namespace sylar
{

Logger::Logger(const std::string& name = "root")
    :name_(name) { }

void Logger::log(LogLevel::Level level, LogEvent::ptr event)
{
    if (level >= level_)
    {
        for(auto& appender : appenders_)
        {
            appender->log(level, event);
        }
    }
}

void Logger::debug(LogEvent::ptr event)
{
    
}
void Logger::info(LogEvent::ptr event)
{
    // debug(LogLevel::INFO, event);
}

void Logger::warn(LogEvent::ptr event)
{

}

void Logger::error(LogEvent::ptr event)
{

}

void Logger::fatal(LogEvent::ptr event)
{

}

void Logger::addAppender(LogAppender::ptr appender)
{
    appenders_.push_back(appender);
}

void Logger::deleteAppender(LogAppender::ptr appender)
{
    for (auto it = appenders_.begin(); it != appenders_.end(); ++it)
    {
        if (*it == appender)
        {
            appenders_.erase(it);
            break;
        }
    }
}

inline void Logger::setLevel(LogLevel::Level val) 
{
    level_ = val;
}

inline LogLevel::Level Logger::getLevel() const 
{
    return level_;
}

}