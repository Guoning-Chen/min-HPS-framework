#include "log_event.h"

namespace sylar
{

LogEvent::LogEvent(LoggerPtr logger, LogLevel::Level level,
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

const std::string& LogEvent::getThreadName() const
{
    return threadName_;
}
std::string LogEvent::getContent() const
{
    return ss_.str();
}

LoggerPtr LogEvent::getLogger() const
{
    return logger_;
}

LogLevel::Level LogEvent::getLevel() const
{
    return level_;
}

std::stringstream& LogEvent::getSS()
{
    return ss_;
}

void LogEvent::format(const char* fmt, ...)
{
    va_list al;
    va_start(al, fmt);
    format(fmt, al); // 调用void format(const char* fmt, va_list al);
    va_end(al);
}

void LogEvent::format(const char* fmt, va_list al)
{
    char* buf = nullptr;
    // 将可变参数列表al以fmt格式写入buf
    const int kLen = vasprintf(&buf, fmt, al);
    if(kLen != -1)
    {
        ss_ << std::string(buf, kLen);
        free(buf);
    }
}


}