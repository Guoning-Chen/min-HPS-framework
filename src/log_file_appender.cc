#include "log_file_appender.h"

namespace sylar
{

FileLogAppender::FileLogAppender(const std::string& filename)
    :filename_(filename)
{

}

void FileLogAppender::log(std::shared_ptr<Logger>logger, LogLevel::Level level, 
                          LogEvent::ptr event)
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