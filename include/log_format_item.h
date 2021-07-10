#ifndef FORMAT_ITEM_H_
#define FORMAT_ITEM_H_

#include "log_formatter.h"

namespace sylar
{

// %m 消息
class MessageFormatItem : public LogFormatter::FormatItem
{
public:
    using FormatItem::FormatItem;
    void format(std::ostream& os, std::shared_ptr<Logger> logger, 
        LogLevel::Level level, LogEvent::ptr event) override;
};

// %p 日志级别
class LevelFormatItem : public LogFormatter::FormatItem
{
public:
    using FormatItem::FormatItem;
    void format(std::ostream& os, std::shared_ptr<Logger> logger, 
        LogLevel::Level level, LogEvent::ptr event) override;
};

// %r 累计时间(ms)
class ElapseFormatItem : public LogFormatter::FormatItem
{
public:
    using FormatItem::FormatItem;
    void format(std::ostream& os, std::shared_ptr<Logger> logger, 
        LogLevel::Level level, LogEvent::ptr event) override;
};

// %c 日志名称
class NameFormatItem : public LogFormatter::FormatItem
{
public:
    using FormatItem::FormatItem;
    void format(std::ostream& os, std::shared_ptr<Logger> logger, 
        LogLevel::Level level, LogEvent::ptr event) override;
};

// %t 线程id
class ThreadIdFormatItem : public LogFormatter::FormatItem
{
public:
    using FormatItem::FormatItem;
    void format(std::ostream& os, std::shared_ptr<Logger> logger, 
        LogLevel::Level level, LogEvent::ptr event) override;
};

// %n 换行
class NewLineFormatItem : public LogFormatter::FormatItem
{
public:
    using FormatItem::FormatItem;
    void format(std::ostream& os, std::shared_ptr<Logger> logger, 
        LogLevel::Level level, LogEvent::ptr event) override;
};

// %d 时间
class DateTimeFormatItem : public LogFormatter::FormatItem
{
public:
    DateTimeFormatItem(const std::string& format = "%Y:%m:%d %H:%M:%S");
    void format(std::ostream& os, std::shared_ptr<Logger> logger, 
        LogLevel::Level level, LogEvent::ptr event) override;
private:
    std::string format_;
};

// %f 文件名
class FilenameFormatItem : public LogFormatter::FormatItem
{
public:
    using FormatItem::FormatItem;
    void format(std::ostream& os, std::shared_ptr<Logger> logger, 
        LogLevel::Level level, LogEvent::ptr event) override;
};

// %l 行号
class LineFormatItem : public LogFormatter::FormatItem
{
public:
    using FormatItem::FormatItem;
    void format(std::ostream& os, std::shared_ptr<Logger> logger, 
        LogLevel::Level level, LogEvent::ptr event) override;
};

// %T Tab
class TabFormatItem : public LogFormatter::FormatItem {
public:
    TabFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << "\t";
    }
private:
    std::string m_string;
};

// %F 协程id
class FiberIdFormatItem : public LogFormatter::FormatItem
{
public:
    using FormatItem::FormatItem;
    void format(std::ostream& os, std::shared_ptr<Logger> logger, 
        LogLevel::Level level, LogEvent::ptr event) override;
};


// 默认格式
class StringFormatItem : public LogFormatter::FormatItem
{
public:
    using FormatItem::FormatItem;
    StringFormatItem(const std::string& str);
    void format(std::ostream& os, std::shared_ptr<Logger> logger, 
        LogLevel::Level level, LogEvent::ptr event) override;
private:
    std::string string_;
};

}

#endif // FORMAT_ITEM_H_