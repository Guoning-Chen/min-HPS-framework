#include "log_file_appender.h"

namespace sylar
{

FileLogAppender::FileLogAppender(const std::string& filename)
    :filename_(filename)
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