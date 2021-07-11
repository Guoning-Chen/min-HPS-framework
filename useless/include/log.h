#ifndef LOG_H_
#define LOG_H_

#include <memory>

namespace sylar
{

class LogLevel;
class Logger;
class LogFormatter;
class StringFormatItem;
class LogEvent;
class LogAppender;
class FileLogAppender;
class StdouLogAppender;

typedef std::shared_ptr<Logger> LoggerPtr;
typedef std::shared_ptr<LogEvent> LogEventPtr;
typedef std::shared_ptr<LogFormatter> LogFormatterPtr;
typedef std::shared_ptr<LogAppender> LogAppenderPtr;

}

# endif // LOG_H_