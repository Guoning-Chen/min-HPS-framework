#ifndef LOG_FORMATTER_H_
#define LOG_FORMATTER_H_


#include <memory>
#include <string>
#include <vector>
#include <map>
#include <functional>

#include "log_event.h"
#include "log_level.h"
#include "logger.h"

namespace sylar
{

// 日志格式器
class LogFormatter
{
public:
    typedef std::shared_ptr<LogFormatter> ptr;
    LogFormatter(const std::string& pattern);

    std::string format(std::shared_ptr<Logger> logger, LogLevel::Level level, 
        LogEvent::ptr event);
public:
    class FormatItem
    {
    public:
        typedef std::shared_ptr<FormatItem> ptr;
        FormatItem(const std::string& format = "");
        virtual ~FormatItem() {}
        virtual void format(std::ostream& os, std::shared_ptr<Logger> logger, 
            LogLevel::Level level, LogEvent::ptr event) = 0;
    };

    void init();
private:
    std::string pattern_;
    std::vector<FormatItem::ptr> items_;
};

}

#endif // LOG_FORMATTER_H_