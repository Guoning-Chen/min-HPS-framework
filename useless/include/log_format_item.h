#ifndef FORMAT_ITEM_H_
#define FORMAT_ITEM_H_

#include "log.h"
#include "log_formatter.h"

namespace sylar
{
    
// (0) %m 消息
class MessageFormatItem : public LogFormatter::FormatItem
{
public:
    using FormatItem::FormatItem;
    void format(std::ostream& os, LoggerPtr logger, 
        LogLevel::Level level, LogEventPtr event) override;
};

// (1) %p 日志级别
class LevelFormatItem : public LogFormatter::FormatItem
{
public:
    using FormatItem::FormatItem;
    void format(std::ostream& os, LoggerPtr logger, 
        LogLevel::Level level, LogEventPtr event) override;
};

// (2) %r 累计时间(ms)
class ElapseFormatItem : public LogFormatter::FormatItem
{
public:
    using FormatItem::FormatItem;
    void format(std::ostream& os, LoggerPtr logger, 
        LogLevel::Level level, LogEventPtr event) override;
};

// (3) %c 日志名称
class NameFormatItem : public LogFormatter::FormatItem
{
public:
    using FormatItem::FormatItem;
    void format(std::ostream& os, LoggerPtr logger, 
        LogLevel::Level level, LogEventPtr event) override;
};

// (4) %t 线程id
class ThreadIdFormatItem : public LogFormatter::FormatItem
{
public:
    using FormatItem::FormatItem;
    void format(std::ostream& os, LoggerPtr logger, 
        LogLevel::Level level, LogEventPtr event) override;
};

// (5) %n 换行
class NewLineFormatItem : public LogFormatter::FormatItem
{
public:
    using FormatItem::FormatItem;
    void format(std::ostream& os, LoggerPtr logger, 
        LogLevel::Level level, LogEventPtr event) override;
};

// (6) %d 时间
class DateTimeFormatItem : public LogFormatter::FormatItem
{
public:
    DateTimeFormatItem(const std::string& format = "%Y:%m:%d %H:%M:%S");
    void format(std::ostream& os, LoggerPtr logger, 
        LogLevel::Level level, LogEventPtr event) override;
private:
    std::string format_;
};

// (7) %f 文件名
class FilenameFormatItem : public LogFormatter::FormatItem
{
public:
    using FormatItem::FormatItem;
    void format(std::ostream& os, LoggerPtr logger, 
        LogLevel::Level level, LogEventPtr event) override;
};

// (8) %l 行号
class LineFormatItem : public LogFormatter::FormatItem
{
public:
    using FormatItem::FormatItem;
    void format(std::ostream& os, LoggerPtr logger, 
        LogLevel::Level level, LogEventPtr event) override;
};

// (9) %T Tab
class TabFormatItem : public LogFormatter::FormatItem {
public:
    TabFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, LoggerPtr logger, 
        LogLevel::Level level, LogEventPtr event) override;
private:
    std::string m_string;
};

// (10) %F 协程id
class FiberIdFormatItem : public LogFormatter::FormatItem
{
public:
    using FormatItem::FormatItem;
    void format(std::ostream& os, LoggerPtr logger, 
        LogLevel::Level level, LogEventPtr event) override;
};

// (11) %N 线程名称
class ThreadNameFormatItem : public LogFormatter::FormatItem
{
public:
    using FormatItem::FormatItem;
    void format(std::ostream& os, LoggerPtr logger, 
        LogLevel::Level level, LogEventPtr event) override;
};

// (12) 默认格式
class StringFormatItem : public LogFormatter::FormatItem
{
public:
    using FormatItem::FormatItem;
    StringFormatItem(const std::string& str);
    void format(std::ostream& os, LoggerPtr logger, 
        LogLevel::Level level, LogEventPtr event) override;
private:
    std::string string_;
};

}

#endif // FORMAT_ITEM_H_