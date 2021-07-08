#include "log_event.h"

namespace sylar
{

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