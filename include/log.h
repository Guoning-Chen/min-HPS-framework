#ifndef LOG_H_
#define LOG_H_

#include <iostream>
#include <string>
#include <memory>
#include <list>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <functional>

#include <cstdint>
#include <cstdarg>

namespace sylar
{

    class LogLevel;
    class Logger;
    class LogFormatter;
    class StringFormatItem;
    class LogEvent;
    class LogAppender;
    class FileLogAppender;
    class StdouLogAppender;

    typedef std::shared_ptr<Logger> LoggerPtr;
    typedef std::shared_ptr<LogEvent> LogEventPtr;
    typedef std::shared_ptr<LogFormatter> LogFormatterPtr;
    typedef std::shared_ptr<LogAppender> LogAppenderPtr;

    // 日志级别
    class LogLevel
    {
    public:
        enum Level
        {
            UNKNOWN = 0,
            DEBUG = 1,
            INFO = 2,
            WARN = 3,
            ERROR = 4,
            FATAL = 5
        };

        static const char *toString(LogLevel::Level level);
        LogLevel::Level fromString(const std::string &str);
    };

    class LogEvent
    {
    public:
        LogEvent(LoggerPtr logger, LogLevel::Level level, const char *file, int32_t line, uint32_t elapse, uint32_t threadId, uint32_t fiberId, uint64_t time, const std::string &threadName);

        // get方法
        const char *getFile() const;
        int32_t getLine() const;
        uint32_t getElapse() const;
        uint32_t getThreadId() const;
        uint32_t getFiberId() const;
        uint64_t getTime() const;
        const std::string &getThreadName() const;
        std::string getContent() const;
        LoggerPtr getLogger() const;
        LogLevel::Level getLevel() const;
        std::stringstream &getSS();

        // 格式化写入日志内容
        void format(const char *fmt, ...);        // 可变参数函数
        void format(const char *fmt, va_list al); // 实际的执行函数
    private:
        const char *file_ = nullptr; // 文件名
        int32_t line_ = 0;           // 行号
        uint32_t elapse_ = 0;        // 程序启动到现在的毫秒
        uint32_t threadId_ = 0;      // 线程id
        uint32_t fiberId_ = 0;       // 协程id
        uint64_t time_ = 0;          // 时间戳
        std::string threadName_;     // 线程名称
        std::stringstream ss_;       // 日志内容流
        LoggerPtr logger_;           // 日志器
        LogLevel::Level level_;      // 日志等级
    };

    // 日志格式器
    class LogFormatter
    {

    public:
        LogFormatter(const std::string &pattern);

        std::string format(LoggerPtr logger, LogLevel::Level level,
                           LogEventPtr event);

    public:
        class FormatItem
        {
        public:
            FormatItem(const std::string &format = "");
            virtual ~FormatItem() {}
            virtual void format(std::ostream &os, LoggerPtr logger,
                                LogLevel::Level level, LogEventPtr event) = 0;
        };
        typedef std::shared_ptr<FormatItem> FormatItemPtr;

        void init();

    private:
        std::string pattern_;
        std::vector<std::shared_ptr<FormatItem>> items_;
    };

    // (0) %m 消息
    class MessageFormatItem : public LogFormatter::FormatItem
    {
    public:
        using FormatItem::FormatItem;
        void format(std::ostream &os, LoggerPtr logger,
                    LogLevel::Level level, LogEventPtr event) override;
    };

    // (1) %p 日志级别
    class LevelFormatItem : public LogFormatter::FormatItem
    {
    public:
        using FormatItem::FormatItem;
        void format(std::ostream &os, LoggerPtr logger,
                    LogLevel::Level level, LogEventPtr event) override;
    };

    // (2) %r 累计时间(ms)
    class ElapseFormatItem : public LogFormatter::FormatItem
    {
    public:
        using FormatItem::FormatItem;
        void format(std::ostream &os, LoggerPtr logger,
                    LogLevel::Level level, LogEventPtr event) override;
    };

    // (3) %c 日志名称
    class NameFormatItem : public LogFormatter::FormatItem
    {
    public:
        using FormatItem::FormatItem;
        void format(std::ostream &os, LoggerPtr logger,
                    LogLevel::Level level, LogEventPtr event) override;
    };

    // (4) %t 线程id
    class ThreadIdFormatItem : public LogFormatter::FormatItem
    {
    public:
        using FormatItem::FormatItem;
        void format(std::ostream &os, LoggerPtr logger,
                    LogLevel::Level level, LogEventPtr event) override;
    };

    // (5) %n 换行
    class NewLineFormatItem : public LogFormatter::FormatItem
    {
    public:
        using FormatItem::FormatItem;
        void format(std::ostream &os, LoggerPtr logger,
                    LogLevel::Level level, LogEventPtr event) override;
    };

    // (6) %d 时间
    class DateTimeFormatItem : public LogFormatter::FormatItem
    {
    public:
        DateTimeFormatItem(const std::string &format = "%Y:%m:%d %H:%M:%S");
        void format(std::ostream &os, LoggerPtr logger,
                    LogLevel::Level level, LogEventPtr event) override;

    private:
        std::string format_;
    };

    // (7) %f 文件名
    class FilenameFormatItem : public LogFormatter::FormatItem
    {
    public:
        using FormatItem::FormatItem;
        void format(std::ostream &os, LoggerPtr logger,
                    LogLevel::Level level, LogEventPtr event) override;
    };

    // (8) %l 行号
    class LineFormatItem : public LogFormatter::FormatItem
    {
    public:
        using FormatItem::FormatItem;
        void format(std::ostream &os, LoggerPtr logger,
                    LogLevel::Level level, LogEventPtr event) override;
    };

    // (9) %T Tab
    class TabFormatItem : public LogFormatter::FormatItem
    {
    public:
        TabFormatItem(const std::string &str = "") {}
        void format(std::ostream &os, LoggerPtr logger,
                    LogLevel::Level level, LogEventPtr event) override;

    private:
        std::string m_string;
    };

    // (10) %F 协程id
    class FiberIdFormatItem : public LogFormatter::FormatItem
    {
    public:
        using FormatItem::FormatItem;
        void format(std::ostream &os, LoggerPtr logger,
                    LogLevel::Level level, LogEventPtr event) override;
    };

    // (11) %N 线程名称
    class ThreadNameFormatItem : public LogFormatter::FormatItem
    {
    public:
        using FormatItem::FormatItem;
        void format(std::ostream &os, LoggerPtr logger,
                    LogLevel::Level level, LogEventPtr event) override;
    };

    // (12) 默认格式
    class StringFormatItem : public LogFormatter::FormatItem
    {
    public:
        using FormatItem::FormatItem;
        StringFormatItem(const std::string &str);
        void format(std::ostream &os, LoggerPtr logger,
                    LogLevel::Level level, LogEventPtr event) override;

    private:
        std::string string_;
    };

    // 日志输出地
    class LogAppender
    {
    public:
        virtual ~LogAppender();

        virtual void log(LoggerPtr, LogLevel::Level level, LogEventPtr event) = 0;

        void setFormatter(LogFormatterPtr formatter);
        LogFormatterPtr getformatter() const;
        LogLevel::Level getLevel() const;
        void setLevel(LogLevel::Level level);

    protected:
        LogLevel::Level level_;
        LogFormatterPtr formatter_;
    };

    // 日志器
    class Logger : public std::enable_shared_from_this<Logger>
    {
    public:
        Logger(const std::string &name = "root");
        // 写入日志并指定日志级别
        void log(LogLevel::Level level, LogEventPtr event);

        // 写入各种类型的日志
        void debug(LogEventPtr event);
        void info(LogEventPtr event);
        void warn(LogEventPtr event);
        void error(LogEventPtr event);
        void fatal(LogEventPtr event);

        void addAppender(LogAppenderPtr appender);
        void deleteAppender(LogAppenderPtr appender);

        LogLevel::Level getLevel() const;
        void setLevel(LogLevel::Level val);

        const std::string &getName() const;

    private:
        std::string name_;                    // 日志名称
        LogLevel::Level level_;               // 日志级别
        std::list<LogAppenderPtr> appenders_; // Appender集合
    };

    // 输出到控制台的Appender
    class StdoutLogAppender : public LogAppender
    {
    public:
        void log(LoggerPtr logger, LogLevel::Level level,
                 LogEventPtr event) override;
    };

    // 输出到文件的Appender
    class FileLogAppender : public LogAppender
    {
    public:
        FileLogAppender(const std::string &filename);
        void log(LoggerPtr logger, LogLevel::Level level, LogEventPtr event) override;

        // 重新打开文件,成功则返回true
        bool reopen();

    private:
        std::string filename_;
        std::ofstream fileStream_;
    };

}

#endif // LOG_H_