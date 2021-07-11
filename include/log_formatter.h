#ifndef LOG_FORMATTER_H_
#define LOG_FORMATTER_H_


#include <memory>
#include <string>
#include <vector>
#include <map>

#include "log.h"
#include "log_event.h"
#include "log_level.h"
#include "logger.h"

namespace sylar
{

// 日志格式器
class LogFormatter
{

public:
    LogFormatter(const std::string& pattern);

    std::string format(LoggerPtr logger, LogLevel::Level level, 
        LogEventPtr event);
public:
    class FormatItem
    {
    public:
        FormatItem(const std::string& format = "");
        virtual ~FormatItem() {}
        virtual void format(std::ostream& os, LoggerPtr logger, 
            LogLevel::Level level, LogEventPtr event) = 0;
    };
    typedef std::shared_ptr<FormatItem> FormatItemPtr;

    void init();
private:
    std::string pattern_;
    std::vector<std::shared_ptr<FormatItem>> items_;
};

}

#endif // LOG_FORMATTER_H_