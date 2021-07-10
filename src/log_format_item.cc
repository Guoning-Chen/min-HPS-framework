#include <ostream>

#include "log_format_item.h"

namespace sylar
{

// message
void MessageFormatItem::format(std::ostream& os, std::shared_ptr<Logger> logger,
    LogLevel::Level level, LogEvent::ptr event)
{
    os << event->getContent();
}

// level
void LevelFormatItem::format(std::ostream& os, std::shared_ptr<Logger> logger,
    LogLevel::Level level, LogEvent::ptr event)
{
    os << LogLevel::toString(level);
}

// elapse
void ElapseFormatItem::format(std::ostream& os, std::shared_ptr<Logger> logger,
    LogLevel::Level level, LogEvent::ptr event)
{
    os << event->getElapse();
}

// name
void NameFormatItem::format(std::ostream& os, std::shared_ptr<Logger> logger,
    LogLevel::Level level, LogEvent::ptr event)
{
    os << logger->getName();
}

// thread id
void ThreadIdFormatItem::format(std::ostream& os, 
    std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)
{
    os << event->getElapse();
}

// new line
void NewLineFormatItem::format(std::ostream& os, 
    std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)
{

}

// string
StringFormatItem::StringFormatItem(const std::string& str)
    : FormatItem(str), string_(str)
{

}

void StringFormatItem::format(std::ostream& os, 
    std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)
{

}

// fiber id
void FiberIdFormatItem::format(std::ostream& os, 
    std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)
{
    os << event->getFiberId();
}

// date time
DateTimeFormatItem::DateTimeFormatItem(
    const std::string& format = "%Y:%m:%d %H:%M:%S")
    :format_(format)
{

}

void DateTimeFormatItem::format(std::ostream& os, 
    std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)
{
    os << event->getTime();
}

// line
void LineFormatItem::format(std::ostream& os, 
    std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)
{
    
}

}
