#include <memory>
#include <list>

#include "log_event.h"
#include "log_level.h"
#include "log_appender.h"

namespace sylar
{

// 日志器
class Logger
{
public:
    typedef std::shared_ptr<Logger> ptr;
    Logger(const std::string& name = "root");
    void log(LogLevel::Level level, LogEvent::ptr event);

    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);
    void deleteAppender(LogAppender::ptr appender);
    LogLevel::Level getLevel() const;
    void setLevel(LogLevel::Level val);
private:
    std::string name_;                      // 日志名称
    LogLevel::Level level_;                 // 日志级别
    std::list<LogAppender::ptr> appenders_; // Appender集合
};

}