#include "log_event.h"

namespace sylar
{

LogEvent::LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level,
        const char* file, int32_t line, uint32_t elapse, uint32_t threadId, 
        uint32_t fiberId, uint64_t time, const std::string& threadName)
    :file_(file)
    ,line_(line)
    ,elapse_(elapse)
    ,threadId_(threadId)
    ,fiberId_(fiberId)
    ,time_(time)
    ,threadName_(threadName)
    ,logger_(logger)
    ,level_(level)
{
    
}

const char* LogEvent::getFile() const
{
    return file_;
}

int32_t LogEvent::getLine() const
{
    return line_;
}

uint32_t LogEvent::getElapse() const
{
    return elapse_;
}

uint32_t LogEvent::getThreadId() const
{
    return threadId_;
}

uint32_t LogEvent::getFiberId() const
{
    return fiberId_;
}

uint64_t LogEvent::getTime() const
{
    return time_;
}

const std::string& LogEvent::getContent() const
{
    return content_;
}


}