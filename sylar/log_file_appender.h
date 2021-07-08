#ifndef FILE_APPENDER_H_
#define FILE_APPENDER_H_

#include <memory>
#include <fstream>

#include "log_appender.h"
#include "log_level.h"
#include "logger.h"

namespace sylar
{

// 定义输出到文件的Appender
class FileLogAppender : public LogAppender
{
public:
    typedef std::shared_ptr<FileLogAppender> ptr;
    FileLogAppender(const std::string& filename);
    void log(std::shared_ptr<Logger>logger, LogLevel::Level level, LogEvent::ptr event) override;

    // 重新打开文件,成功则返回true
    bool reopen();
private:
    std::string filename_;
    std::ofstream fileStream_;
};

}

#endif // FILE_APPENDER_H_