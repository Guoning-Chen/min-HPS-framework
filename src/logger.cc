#include "logger.h"

using namespace sylar;

namespace sylar
{

Logger::Logger(const std::string& name)
    :name_(name) { }

void Logger::log(LogLevel::Level level, LogEventPtr event)
{
    if (level >= level_)
    {
        for(auto& appender : appenders_)
        {
            auto self = shared_from_this();
            appender->log(self, level, event);
        }
    }
}

void Logger::debug(LogEventPtr event)
{
    
}
void Logger::info(LogEventPtr event)
{
    // debug(LogLevel::INFO, event);
}

void Logger::warn(LogEventPtr event)
{

}

void Logger::error(LogEventPtr event)
{

}

void Logger::fatal(LogEventPtr event)
{

}

void Logger::addAppender(LogAppenderPtr appender)
{
    appenders_.push_back(appender);
}

void Logger::deleteAppender(LogAppenderPtr appender)
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

inline const std::string& Logger::getName() const
{
    return name_;
}

}