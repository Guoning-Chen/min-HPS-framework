#include <memory>

#include "log_appender.h"
#include "log_level.h"
#include "log_event.h"

namespace sylar
{

// 定义输出到控制台的Appender
class StdoutLogAppender : public LogAppender
{
public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;
    void log(LogLevel::Level level, LogEvent::ptr event) override;
private:
};

}