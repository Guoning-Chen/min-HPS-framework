#ifndef STDOUT_APPENDER_H_
#define STDOUT_APPENDER_H_

#include <memory>

#include "log.h"
#include "log_appender.h"
#include "log_level.h"
#include "log_event.h"

namespace sylar
{

// 定义输出到控制台的Appender
class StdoutLogAppender : public LogAppender
{
public:
    void log(LoggerPtr logger, LogLevel::Level level, 
        LogEventPtr event) override;
};

}

#endif // STDOUT_APPENDER_H_