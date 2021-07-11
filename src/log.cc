#include "log.h"

// LogLevel
namespace sylar
{
    const char *LogLevel::toString(LogLevel::Level level)
    {
        switch (level)
        {
#define ENUM2STRIG(name) \
    case LogLevel::name: \
        return #name;    \
        break;
            ENUM2STRIG(DEBUG);
            ENUM2STRIG(INFO);
            ENUM2STRIG(WARN);
            ENUM2STRIG(ERROR);
            ENUM2STRIG(FATAL);
#undef ENUM2STRIG
        default:
            return "UNKNOWN";
        }
        return "UNKNOWN";
    }

    LogLevel::Level LogLevel::fromString(const std::string &str)
    {
#define XX(level, v)            \
    if (str == #v)              \
    {                           \
        return LogLevel::level; \
    }
        XX(DEBUG, debug);
        XX(INFO, info);
        XX(WARN, warn);
        XX(ERROR, error);
        XX(FATAL, fatal);

        XX(DEBUG, DEBUG);
        XX(INFO, INFO);
        XX(WARN, WARN);
        XX(ERROR, ERROR);
        XX(FATAL, FATAL);
        return LogLevel::UNKNOWN;
#undef XX
    }

}
// LogEvent
namespace sylar
{
    LogEvent::LogEvent(LoggerPtr logger, LogLevel::Level level,
                       const char *file, int32_t line, uint32_t elapse, uint32_t threadId,
                       uint32_t fiberId, uint64_t time, const std::string &threadName)
        : file_(file), line_(line), elapse_(elapse), threadId_(threadId), fiberId_(fiberId), time_(time), threadName_(threadName), logger_(logger), level_(level)
    {
    }

    const char *LogEvent::getFile() const
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

    const std::string &LogEvent::getThreadName() const
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

    std::stringstream &LogEvent::getSS()
    {
        return ss_;
    }

    void LogEvent::format(const char *fmt, ...)
    {
        va_list al;
        va_start(al, fmt);
        format(fmt, al); // 调用void format(const char* fmt, va_list al);
        va_end(al);
    }

    void LogEvent::format(const char *fmt, va_list al)
    {
        char *buf = nullptr;
        // 将可变参数列表al以fmt格式写入buf
        const int kLen = vasprintf(&buf, fmt, al);
        if (kLen != -1)
        {
            ss_ << std::string(buf, kLen);
            free(buf);
        }
    }
}

// LogAppender
namespace sylar
{
    LogAppender::~LogAppender()
    {
    }

    inline void LogAppender::setFormatter(LogFormatterPtr formatter)
    {
        formatter_ = formatter;
    }

    inline LogFormatterPtr LogAppender::getformatter() const
    {
        return formatter_;
    }

    inline LogLevel::Level LogAppender::getLevel() const
    {
        return level_;
    }

    inline void LogAppender::setLevel(LogLevel::Level level)
    {
        level_ = level;
    }
}

// LogFormatter
namespace sylar
{
    LogFormatter::LogFormatter(const std::string &pattern)
        : pattern_(pattern)
    {
    }

    std::string LogFormatter::format(LoggerPtr logger,
                                     LogLevel::Level level, LogEventPtr event)
    {
        std::stringstream ss;
        for (auto &item : items_)
            item->format(ss, logger, level, event);
        return ss.str();
    }

    void LogFormatter::init()
    {
        // %xxx, %xxx{xxx} %%
        // str, format, type
        std::vector<std::tuple<std::string, std::string, int>> v;
        std::string nstr;
        for (size_t i = 0; i < pattern_.size(); ++i)
        {
            if (pattern_[i] != '%')
            {
                nstr.append(1, pattern_[i]);
                continue;
            }

            if (i + 1 < pattern_.size())
            {
                if (pattern_[i + 1] == '%')
                {
                    nstr.append(1, '%');
                    continue;
                }
            }

            size_t n = i + 1;
            int status = 0;
            size_t begin = 0;

            std::string str, format;
            while (n < pattern_.size())
            {
                if (isspace(pattern_[n]))
                    break;
                if (status == 0)
                {
                    if (pattern_[n] == '{')
                    {
                        str = pattern_.substr(i + 1, n - i - 1);
                        status = 1;
                        begin = n;
                        ++n;
                        continue;
                    }
                }
                if (status == 1)
                {
                    if (pattern_[n] == '}')
                    {
                        format = pattern_.substr(begin + 1, n - begin - 1);
                        status = 2;
                        break;
                    }
                }
            }
            if (status == 0)
            {
                if (nstr.empty())
                    v.push_back(std::make_tuple(nstr, "", 0));
                str = pattern_.substr(i + 1, n - i - 1);
                v.push_back(std::make_tuple(str, format, 1));
                i = n;
            }
            else if (status == 1)
            {
                std::cout << "pattern parse error: " << pattern_ << " - " << pattern_.substr(i) << std::endl;
                v.push_back(std::make_tuple("<<pattern_error>>", format, 0));
            }
            else if (status == 2)
            {
                if (!nstr.empty())
                    v.push_back(std::make_tuple(nstr, "", 0));
                v.push_back(std::make_tuple(str, format, 1));
            }
        }
        if (!nstr.empty())
            v.push_back(std::make_tuple(nstr, "", 0));

        static std::map<std::string,
                        std::function<FormatItemPtr(const std::string &str)>>
            formatItems = {
#define CALL_CONSTRUCTOR(str, C)                                                     \
    {                                                                                \
#str, [](const std::string &format) { return FormatItemPtr(new C(format)); } \
    }

                CALL_CONSTRUCTOR(m, MessageFormatItem),    //m:消息
                CALL_CONSTRUCTOR(p, LevelFormatItem),      //p:日志级别
                CALL_CONSTRUCTOR(r, ElapseFormatItem),     //r:累计毫秒数
                CALL_CONSTRUCTOR(c, NameFormatItem),       //c:日志名称
                CALL_CONSTRUCTOR(t, ThreadIdFormatItem),   //t:线程id
                CALL_CONSTRUCTOR(n, NewLineFormatItem),    //n:换行
                CALL_CONSTRUCTOR(d, DateTimeFormatItem),   //d:时间
                CALL_CONSTRUCTOR(f, FilenameFormatItem),   //f:文件名
                CALL_CONSTRUCTOR(l, LineFormatItem),       //l:行号
                CALL_CONSTRUCTOR(T, TabFormatItem),        //T:Tab
                CALL_CONSTRUCTOR(F, FiberIdFormatItem),    //F:协程id
                CALL_CONSTRUCTOR(N, ThreadNameFormatItem), //N:线程名称
#undef CALL_CONSTRUCTOR
            };
        // for (auto& item : items_)
        // {
        //     if (std::get<2>(item) == 0)
        //     {
        //         const std::string& str = std::get(0)(item);
        //         FormatItemPtr ptr = FormatItemPtr(new StringFormatItem(format));
        //         items_.push_back(ptr);
        //     }
        //     else
        //     {
        //         const std::string& str = std::get<0>(item);
        //         auto it = formatItems.find(str);
        //         if (it == formatItems.end())
        //         {
        //             const std::string str = std::get<0>(item);
        //             FormatItemPtr ptr = FormatItemPtr(new StringFormatItem("<<error_format %" + str + ">>"))
        //             items_.push_back(ptr);
        //         }
        //         else
        //         {
        //             items_.push_back(it->second(std::get<1>(item)));
        //         }
        //     }

        //     std::cout << std::get<0>(item) << " - " << std::get<1>(item) <<
        //                  " - " << std::get<2>(item) << std::endl;
        // }
    }

    LogFormatter::FormatItem::FormatItem(const std::string &format)
    {
    }

}

// 各种FormateItem
namespace sylar
{
    // ================== 各种FormatItem类 =======================================//
    // ===================== (0) %m 消息 =================================//
    void MessageFormatItem::format(std::ostream &os, LoggerPtr logger,
                                   LogLevel::Level level, LogEventPtr event)
    {
        os << event->getContent();
    }

    // ===================== (1) %p 日志级别 =================================//
    void LevelFormatItem::format(std::ostream &os, LoggerPtr logger,
                                 LogLevel::Level level, LogEventPtr event)
    {
        os << LogLevel::toString(level);
    }

    // ===================== (2) %r 累计时间(ms) =================================//
    void ElapseFormatItem::format(std::ostream &os, LoggerPtr logger,
                                  LogLevel::Level level, LogEventPtr event)
    {
        os << event->getElapse();
    }

    // ===================== (3) %c 日志名称 =================================//
    void NameFormatItem::format(std::ostream &os, LoggerPtr logger,
                                LogLevel::Level level, LogEventPtr event)
    {
        os << event->getLogger()->getName();
    }

    // ===================== (4) %t 线程id =================================//
    void ThreadIdFormatItem::format(std::ostream &os,
                                    LoggerPtr logger, LogLevel::Level level, LogEventPtr event)
    {
        os << event->getThreadId();
    }

    // ===================== (5) %n 换行 =================================//
    void NewLineFormatItem::format(std::ostream &os,
                                   LoggerPtr logger, LogLevel::Level level, LogEventPtr event)
    {
        os << std::endl;
    }

    // ===================== (6) %d 时间 =================================//
    DateTimeFormatItem::DateTimeFormatItem(const std::string &format)
        : format_(format)
    {
        if (format.empty())
            format_ = "%Y-%m-%d %H:%M:%S";
    }

    void DateTimeFormatItem::format(std::ostream &os,
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
    void FilenameFormatItem::format(std::ostream &os,
                                    LoggerPtr logger, LogLevel::Level level, LogEventPtr event)
    {
        os << event->getFile();
    }

    // =====================  (8) %l 行号 =================================//
    void LineFormatItem::format(std::ostream &os,
                                LoggerPtr logger, LogLevel::Level level, LogEventPtr event)
    {
        os << event->getLine();
    }

    // ===================== (9) %T Tab =================================//
    void TabFormatItem::format(std::ostream &os,
                               LoggerPtr logger, LogLevel::Level level, LogEventPtr event)
    {
        os << "\t";
    }

    // ===================== (10) %F 协程id =================================//
    void FiberIdFormatItem::format(std::ostream &os,
                                   LoggerPtr logger, LogLevel::Level level, LogEventPtr event)
    {
        os << event->getFiberId();
    }

    // ===================== (11) %N 线程名称 =================================//
    void ThreadNameFormatItem::format(std::ostream &os,
                                      LoggerPtr logger, LogLevel::Level level, LogEventPtr event)
    {
        os << event->getThreadName();
    }

    // ===================== (12) 默认格式 =================================//
    StringFormatItem::StringFormatItem(const std::string &str)
        : string_(str)
    {
    }

    void StringFormatItem::format(std::ostream &os,
                                  LoggerPtr logger, LogLevel::Level level, LogEventPtr event)
    {
        os << string_;
    }
}

// Logger
namespace sylar
{
    Logger::Logger(const std::string &name)
        : name_(name) {}

    void Logger::log(LogLevel::Level level, LogEventPtr event)
    {
        if (level >= level_)
        {
            for (auto &appender : appenders_)
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

    inline const std::string &Logger::getName() const
    {
        return name_;
    }
}

// FileLogAppender
namespace sylar
{
    FileLogAppender::FileLogAppender(const std::string &filename)
        : filename_(filename)
    {
    }

    void FileLogAppender::log(LoggerPtr logger, LogLevel::Level level,
                              LogEventPtr event)
    {
        if (level >= level_)
            fileStream_ << formatter_->format(logger, level, event);
    }

    bool FileLogAppender::reopen()
    {
        if (fileStream_)
            fileStream_.close();
        fileStream_.open(filename_);
        return !fileStream_;
    }
}

//StdoutLogAppender
namespace sylar
{

    void StdoutLogAppender::log(LoggerPtr logger, LogLevel::Level level,
                                LogEventPtr event)
    {
        if (level >= level_)
            std::cout << formatter_->format(logger, level, event);
    }

}