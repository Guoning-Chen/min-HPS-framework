#ifndef FILE_APPENDER_H_
#define FILE_APPENDER_H_

#include <memory>
#include <fstream>

#include "log.h"
#include "log_appender.h"
#include "log_level.h"
#include "logger.h"
#include "log_event.h"

namespace sylar
{

// 定义输出到文件的Appender
class FileLogAppender : public LogAppender
{
public:
    FileLogAppender(const std::string& filename);
    void log(LoggerPtr logger, LogLevel::Level level, LogEventPtr event) override;

    // 重新打开文件,成功则返回true
    bool reopen();
private:
    std::string filename_;
    std::ofstream fileStream_;
};

}

#endif // FILE_APPENDER_H_