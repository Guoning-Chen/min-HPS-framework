#include <memory>
#include "log_formatter.h"
#include "log_level.h"

namespace sylar
{

// 日志输出地
class LogAppender
{
public:
    typedef std::shared_ptr<LogAppender> ptr;
    virtual ~LogAppender();

    virtual void log(LogLevel::Level level, LogEvent::ptr event) = 0; // 纯虚函数

    void setFormatter(LogFormatter::ptr formatter);
    LogFormatter::ptr getformatter() const;
protected:
    LogLevel::Level level_;
    LogFormatter::ptr formatter_;
};

}