#ifndef FORMAT_ITEM_H_
#define FORMAT_ITEM_H_

#include "log_formatter.h"

namespace sylar
{

// message
class MessageFormatItem : public LogFormatter::FormatItem
{
public:
    void format(std::ostream& os, std::shared_ptr<Logger> logger, 
        LogLevel::Level level, LogEvent::ptr event) override;
};

// level
class LevelFormatItem : public LogFormatter::FormatItem
{
public:
    void format(std::ostream& os, std::shared_ptr<Logger> logger, 
        LogLevel::Level level, LogEvent::ptr event) override;
};

// elapse
class ElapseFormatItem : public LogFormatter::FormatItem
{
public:
    void format(std::ostream& os, std::shared_ptr<Logger> logger, 
        LogLevel::Level level, LogEvent::ptr event) override;
};

// name
class NameFormatItem : public LogFormatter::FormatItem
{
public:
    void format(std::ostream& os, std::shared_ptr<Logger> logger, 
        LogLevel::Level level, LogEvent::ptr event) override;
};

// thread id
class ThreadIdFormatItem : public LogFormatter::FormatItem
{
public:
    void format(std::ostream& os, std::shared_ptr<Logger> logger, 
        LogLevel::Level level, LogEvent::ptr event) override;
};

// new line(回车换行)
class NewLineFormatItem : public LogFormatter::FormatItem
{
public:
    void format(std::ostream& os, std::shared_ptr<Logger> logger, 
        LogLevel::Level level, LogEvent::ptr event) override;
};

// string(其他)
class StringFormatItem : public LogFormatter::FormatItem
{
public:
    StringFormatItem(const std::string& str);
    void format(std::ostream& os, std::shared_ptr<Logger> logger, 
        LogLevel::Level level, LogEvent::ptr event) override;
private:
    std::string string_;
};

// fiber id
class FiberIdFormatItem : public LogFormatter::FormatItem
{
public:
    void format(std::ostream& os, std::shared_ptr<Logger> logger, 
        LogLevel::Level level, LogEvent::ptr event) override;
};

// time
class DateTimeFormatItem : public LogFormatter::FormatItem
{
public:
    DateTimeFormatItem(const std::string& format = "%Y:%m:%d %H:%M:%S");
    void format(std::ostream& os, std::shared_ptr<Logger> logger, 
        LogLevel::Level level, LogEvent::ptr event) override;
private:
    std::string format_;
};

// filename
class FilenameFormatItem : public LogFormatter::FormatItem
{
public:
    void format(std::ostream& os, std::shared_ptr<Logger> logger, 
        LogLevel::Level level, LogEvent::ptr event) override;
};

// line
class LineFormatItem : public LogFormatter::FormatItem
{
public:
    void format(std::ostream& os, std::shared_ptr<Logger> logger, 
        LogLevel::Level level, LogEvent::ptr event) override;
};

}

#endif // FORMAT_ITEM_H_