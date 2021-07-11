#include <ostream>

#include "logger.h"
#include "log_format_item.h"

namespace sylar
{

// ===================== (0) %m 消息 =================================//
void MessageFormatItem::format(std::ostream& os, LoggerPtr logger,
    LogLevel::Level level, LogEventPtr event)
{
    os << event->getContent();
}

// ===================== (1) %p 日志级别 =================================//
void LevelFormatItem::format(std::ostream& os, LoggerPtr logger,
    LogLevel::Level level, LogEventPtr event)
{
    os << LogLevel::toString(level);
}

// ===================== (2) %r 累计时间(ms) =================================//
void ElapseFormatItem::format(std::ostream& os, LoggerPtr logger,
    LogLevel::Level level, LogEventPtr event)
{
    os << event->getElapse();
}

// ===================== (3) %c 日志名称 =================================//
void NameFormatItem::format(std::ostream& os, LoggerPtr logger,
    LogLevel::Level level, LogEventPtr event)
{
    os << event->getLogger()->getName();
}

// ===================== (4) %t 线程id =================================//
void ThreadIdFormatItem::format(std::ostream& os, 
    LoggerPtr logger, LogLevel::Level level, LogEventPtr event)
{
    os << event->getThreadId();
}

// ===================== (5) %n 换行 =================================//
void NewLineFormatItem::format(std::ostream& os, 
    LoggerPtr logger, LogLevel::Level level, LogEventPtr event)
{
    os << std::endl;
}

// ===================== (6) %d 时间 =================================//
DateTimeFormatItem::DateTimeFormatItem(const std::string& format)
    :format_(format)
{
    if(format.empty())
        format_ = "%Y-%m-%d %H:%M:%S";
}

void DateTimeFormatItem::format(std::ostream& os, 
    LoggerPtr logger, LogLevel::Level level, LogEventPtr event)
{
    struct tm tm;
    time_t time = event->getTime();
    localtime_r(&time, &tm);
    char buf[64];
    strftime(buf, sizeof(buf), format_.c_str(), &tm);
    os << buf;
}

// ===================== (7) %f 文件名 =================================//
void FilenameFormatItem::format(std::ostream& os, 
    LoggerPtr logger, LogLevel::Level level, LogEventPtr event)
{
    os << event->getFile();
}

// =====================  (8) %l 行号 =================================//
void LineFormatItem::format(std::ostream& os, 
    LoggerPtr logger, LogLevel::Level level, LogEventPtr event)
{
    os << event->getLine();
}

// ===================== (9) %T Tab =================================//
void TabFormatItem::format(std::ostream& os, 
    LoggerPtr logger, LogLevel::Level level, LogEventPtr event)
{
    os << "\t";
}

// ===================== (10) %F 协程id =================================//
void FiberIdFormatItem::format(std::ostream& os, 
    LoggerPtr logger, LogLevel::Level level, LogEventPtr event)
{
    os << event->getFiberId();
}

// ===================== (11) %N 线程名称 =================================//
void ThreadNameFormatItem::format(std::ostream& os, 
    LoggerPtr logger, LogLevel::Level level, LogEventPtr event)
{
    os << event->getThreadName();
}


// ===================== (12) 默认格式 =================================//
StringFormatItem::StringFormatItem(const std::string& str)
    : string_(str)
{

}

void StringFormatItem::format(std::ostream& os, 
    LoggerPtr logger, LogLevel::Level level, LogEventPtr event)
{
    os << string_;
}

}
