#include "file_appender.h"

namespace sylar
{

FileLogAppender::FileLogAppender(const std::string& filename)
    :filename_(filename_)
{

}

void FileLogAppender::log(LogLevel::Level level, LogEvent::ptr event)
{
    if (level >= level_)
        fileStream_ << formatter_->format(event);
}

bool FileLogAppender::reopen()
{
    if (fileStream_)
        fileStream_.close();
    fileStream_.open(filename_);
    return !fileStream_;
}


}